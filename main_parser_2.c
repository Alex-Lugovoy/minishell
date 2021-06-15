#include "minishell.h"

t_command	*left_redirect1(t_command *com, t_command *start, int gg)
{
	com->redir_left = ft_strdup(start->next->command);
	gg = open(com->redir_left, O_RDWR);
	close(gg);
	delete_current_parser(start->next);
	if (start->back != 0)
	{
		start = start->back;
		delete_current_parser(start->next);
	}
	else
	{
		start = start->next;
		if (start)
		{
			delete_current_parser(start->back);
			start->back = 0;
		}
	}
	return (start);
}

t_command	*left_redirect2(t_command *com, t_command *start,
	int gg, t_untils *untils)
{
	start = com->next->next;
	if (start != 0)
		start->redir_double_right = ft_strdup(com->next->command);
	gg = open(com->next->command, O_RDWR);
	if (gg == -1)
	{
		untils->status = 1;
		printf("%s: no such file or directory\n", com->next->command);
		return (0);
	}
	close(gg);
	return (start);
}

t_command	*right_redirect1(t_command *com, t_command *start, int gg)
{
	ft_free(com->redir_right);
	com->redir_right = ft_strdup(start->next->command);
	gg = open(com->redir_right, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	close (gg);
	delete_current_parser(start->next);
	if (start->back != 0)
	{
		start = start->back;
		delete_current_parser(start->next);
	}
	else
	{
		start = start->next;
		if (start)
		{
			delete_current_parser(start->back);
			start->back = 0;
		}
	}
	return (start);
}

t_command	*right_double_redirect1(t_command *com, t_command *start, int gg)
{
	ft_free(com->redir_right);
	com->redir_right = ft_strdup(start->next->command);
	gg = open(com->redir_right, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	close (gg);
	delete_current_parser(start->next);
	if (start->back != 0)
	{
		start = start->back;
		delete_current_parser(start->next);
	}
	else
	{
		start = start->next;
		if (start)
		{
			delete_current_parser(start->back);
			start->back = 0;
		}
	}
	return (start);
}

t_command	*right_double_redirect_22(t_command *com, t_command *start, int gg)
{
	start = com->next->next;
	if (start != 0)
		start->redir_double_right = ft_strdup(com->next->command);
	gg = open(com->next->command, O_CREAT | O_WRONLY | O_APPEND, 0777);
	close (gg);
	return (start);
}
