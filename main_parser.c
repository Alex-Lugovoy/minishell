#include "minishell.h"

t_command	*redirect_check(t_command *com, t_untils *untils)
{
	t_command	*start;
	int			gg;

	start = com;
	com = redirect_check_2(start, com, untils, 0);
	start = com;
	while (start)
	{
		if (start->command[0] == '>' && start->command[1] == '>')
		{
			right_double_redirect1(com, start, 0);
		}
		else if (start->command[0] == '>')
		{
			right_redirect1(com, start, 0);
		}
		else if (start->command[0] == '<')
		{
			start = left_redirect1(com, start, 0);
		}
		start = start->next;
	}
	return (com);
}

void	connect_stdio_to_pipes(int prev_fds[], int next_fds[])
{
	if (prev_fds[0] >= 0)
	{
		dup2(prev_fds[0], 0);
		close(prev_fds[0]);
		close(prev_fds[1]);
	}
	if (next_fds[1] >= 0)
	{
		dup2(next_fds[1], 1);
		close(next_fds[1]);
		close(next_fds[0]);
	}
}

int	count_pp(t_command *start)
{
	int	count_pipes;

	count_pipes = 0;
	while (start)
	{
		if (start->command[0] == '|' && start->command[1] == '\0')
			count_pipes++;
		start = start->next;
	}
	return (count_pipes);
}

void	bsopia_func(t_command *com, int i, t_untils *untils)
{
	t_command	*start;
	char		*tmp;
	int			count_pipes;

	start = com;
	count_pipes = count_pp(start);
	start = com;
	if (count_pipes == 0)
	{
		if (fork_without_pip(com, untils))
			return ;
		if (check_buildin(start->command))
			child_without_pip(start, untils);
		else
			bsophia_function(com, untils);
	}
	else
		children_pip(start, count_pipes, untils);
}

void	main_parser(char *str, t_untils *untils)
{
	t_command	*start;
	t_command	*current_command;

	start = 0;
	start = parser_into_list(str, untils);
	if (start != 0)
		printf("%s\n", start->command);
	ft_free(start);
}
