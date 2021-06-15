#include "minishell.h"

static int	check_arg(t_command *list, t_untils *untils)
{
	if (!(list->next))
	{
		print_export(untils->env, 0, 0);
		check_redir(list, 1, untils);
		return (0);
	}
	return (1);
}

static void	add_arg(t_command *list, t_untils *untils)
{
	while (list->next)
	{
		if (list->next)
		{
			list = list->next;
			export_add(untils->env, list->command, untils);
		}
	}
}

void	execute_export(t_untils *untils, t_command *list)
{
	if (!(check_arg(list, untils)))
		return ;
	list = list->next;
	while (list->next)
	{
		if (check_name(list->command))
			check_redir(list, 1, untils);
		list = list->next;
	}
	if (check_name(list->command))
		check_redir(list, 1, untils);
	while (list->back)
	{
		if (!(ft_strcmp(list->command, "export")))
		{
			check_redir(list, 1, untils);
			break ;
		}
		list = list->back;
	}
	add_arg(list, untils);
}
