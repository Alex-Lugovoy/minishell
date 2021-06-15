#include "minishell.h"

static void	without_pip_2(t_command *start, t_untils *untils)
{
	char	*command;
	char	*commd;
	int		i;

	command = NULL;
	commd = ft_strjoin_line("/", untils->command_ex);
	i = -1;
	if (!check_redir(start, 2, untils))
		exit(1);
	while (untils->bin[++i] != NULL)
	{
		command = ft_strjoin_line(untils->bin[i], commd);
		execve(command, untils->arguments, untils->env);
		ft_free(command);
	}
	ft_free(commd);
	if (untils->bin[i] == NULL && ft_strcmp(untils->command_ex, "minishell")
		&& ft_strcmp(untils->command_ex, "./minishell")
		&& ft_strcmp(untils->command_ex, "$?"))
		exit(127);
	if (!(ft_strcmp(untils->command_ex, "$?")))
	{
		printf("%d : command not found", untils->status);
		exit(127);
	}
}

static void	without_pip(t_command *start, t_untils *untils)
{
	t_command	*com;
	int			i;

	com = start;
	i = 0;
	untils->path = find_path(untils);
	untils->bin = ft_split(untils->path, ':');
	while (start)
	{
		start = start->next;
		i++;
	}
	untils->arguments = (char **)malloc(i * sizeof(char *) + 1);
	start = com;
	i = 0;
	while (start)
	{
		untils->arguments[i] = ft_strdup_b(start->command);
		start = start->next;
		i++;
	}
	untils->arguments[i] = NULL;
	start = com;
}

static void	check_bin_1(t_command *start, t_untils *untils)
{
	char	*tmp;

	if (check_bin(start->command))
	{
		if (!check_redir(start, 2, untils))
			exit(1);
		work_bin(start, untils);
	}
	tmp = find_path(untils);
	if (!(tmp) && !(check_bin(start->command)))
		exit(127);
	ft_free(tmp);
	ft_free(untils->path);
}

void	child_without_pip(t_command *start, t_untils *untils)
{
	int	process[1];

	ft_free(untils->command_ex);
	untils->command_ex = ft_strdup_b(start->command);
	process[0] = fork();
	if (process[0] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		check_bin_1(start, untils);
		without_pip(start, untils);
		without_pip_2(start, untils);
	}
	else
	{
		waitpid(process[0], &untils->status, 0);
		untils->status = untils->status / 256;
		if (untils->status == 127 && ft_strcmp(untils->command_ex, "$?")
			&& !(check_bin(start->command)))
			printf("%s: command not found\n", untils->command_ex);
	}
}
