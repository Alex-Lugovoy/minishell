#include "minishell.h"

static int	right(t_command *list, t_untils *untils, int i)
{
	if (list->redir_right != NULL && i == 2)
	{
		untils->fd_out = open(list->redir_right,
				O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (untils->fd_out < 0)
		{
			printf("%s: %s\n", list->redir_right, strerror(errno));
			untils->status = 1;
			return (0);
		}
		untils->std_out = dup(1);
		dup2(untils->fd_out, 1);
		close(untils->fd_out);
	}
	return (1);
}

static int	double_right(t_command *list, t_untils *untils, int i)
{
	if (list->redir_double_right != NULL && i == 2)
	{
		untils->fd_out = open(list->redir_double_right,
				O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (untils->fd_out < 0)
		{
			printf("%s: %s\n", list->redir_double_right, strerror(errno));
			untils->status = 1;
			return (0);
		}
		untils->std_out = dup(1);
		dup2(untils->fd_out, 1);
		close(untils->fd_out);
	}
	return (1);
}

static int	left(t_command *list, t_untils *untils, int i)
{
	if (list->redir_left != NULL && i == 2)
	{
		untils->fd_in = open(list->redir_left, O_RDWR);
		if (untils->fd_in < 0)
		{
			printf("%s: %s\n", list->redir_left, strerror(errno));
			untils->status = 1;
			return (0);
		}
		untils->std_in = dup(0);
		dup2(untils->fd_in, 0);
		close(untils->fd_in);
	}
	return (1);
}

int	check_redir(t_command *list, int i, t_untils *untils)
{
	if (right(list, untils, i) == 0)
		return (0);
	if (double_right(list, untils, i) == 0)
		return (0);
	if (left(list, untils, i) == 0)
		return (0);
	if (i == 1)
	{
		if (untils->fd_out != 99)
		{
			close(untils->fd_out);
			dup2(untils->std_out, 1);
			close(untils->std_out);
		}
		if (untils->fd_in != 99)
		{
			close(untils->fd_in);
			dup2(untils->std_in, 0);
			close(untils->std_in);
		}
	}
	return (1);
}
