#include "minishell.h"

static void	test2(t_untils *untils, int i, t_command **command_pipes)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	connect_stdio_to_pipes(untils->prev_pipe_fds, untils->next_pipe_fds);
	work_pipes(untils, command_pipes[i]);
}

static void	test1(t_untils *untils, int i, int count_pipes)
{
	untils->prev_pipe_fds[0] = untils->next_pipe_fds[0];
	untils->prev_pipe_fds[1] = untils->next_pipe_fds[1];
	if (i != count_pipes)
		pipe(untils->next_pipe_fds);
	else
	{
		untils->next_pipe_fds[0] = -1;
		untils->next_pipe_fds[1] = -1;
	}
}

static void	pipe_wwork(t_untils *untils, t_command **command_pipes,
	int count_pipes)
{
	int	i;
	int	j;
	int	*process;

	i = -1;
	j = -1;
	process = (int *)malloc(sizeof(int) * (count_pipes + 1));
	while (++i < count_pipes + 1)
	{
		test1(untils, i, count_pipes);
		process[++j] = fork();
		if (process[j] == 0)
			test2(untils, i, command_pipes);
		close(untils->prev_pipe_fds[0]);
		close(untils->prev_pipe_fds[1]);
	}
	j = -1;
	while (++j < count_pipes + 1)
	{
		waitpid(process[j], &(untils->status), 0);
		untils->status = untils->status / 256;
		if (untils->status == 127)
			printf("%s: command not found\n", command_pipes[j]->command);
	}
	free(process);
}

static void	init_pipe(int i, int count_pipes, t_command **command_pipes,
	t_untils *untils)
{
	int	j;

	untils->next_pipe_fds[0] = -1;
	untils->next_pipe_fds[1] = -1;
	j = 0;
	pipe_wwork(untils, command_pipes, count_pipes);
	j = 0;
	while (j < count_pipes + 1)
	{
		ft_lstclear_command(&command_pipes[j]);
		j++;
	}
	ft_free(command_pipes);
}

void	children_pip(t_command *start, int count_pipes, t_untils *untils)
{
	int			j;
	t_command	**command_pipes;
	t_command	*current_pipe;

	current_pipe = 0;
	command_pipes = malloc(sizeof(t_command *) * (count_pipes + 1));
	command_pipes[count_pipes] = 0;
	j = 0;
	while (start)
	{
		if (start->command[0] == '|')
		{
			command_pipes[j] = current_pipe;
			current_pipe = 0;
			j++;
		}
		else
			ft_lstadd_back_parser(&current_pipe,
				ft_lstnew_parser(ft_strdup_b(start->command), 0));
		start = start->next;
	}
	if (current_pipe != 0)
		command_pipes[j] = current_pipe;
	init_pipe(0, count_pipes, command_pipes, untils);
}
