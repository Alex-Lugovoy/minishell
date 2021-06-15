#include "minishell.h"

t_command	*redirect_check_2(t_command *start, t_command *com,
	t_untils *untils, int gg)
{
	while (start != 0 && (start->command[0] == '>' || start->command[0] == '<'))
	{
		if (com->command[0] == '>' && com->command[1] == '>')
		{
			start = right_double_redirect_22(com, start, 0);
			if (start == 0)
				return (start);
		}
		if (com->command[0] == '>' && com->command[1] == '\0')
		{
			start = com->next->next;
			gg = open(com->next->command, O_CREAT | O_WRONLY | O_TRUNC, 0777);
			close (gg);
			if (start == 0)
				return (start);
		}
		if (com->command[0] == '<' && com->command[1] == '\0')
		{
			start = left_redirect2(com, start, 0, untils);
			if (start == 0)
				return (start);
		}
		com = start;
	}
	return (com);
}

int	ccmd(t_cttb *cttb)
{
	if (cttb->current->special_array[cttb->j_env] == 0
		|| cttb->current->special_array[cttb->j_env] == 5
		|| cttb->current->symbol[cttb->j_env] == ';'
		|| cttb->current->special_array[cttb->j_env] == 3
		|| (cttb->current->special_array[0] == 2
			&& cttb->current->special_array[cttb->j_env] == 2))
		return (1);
	return (0);
}

t_command	*send_command_to_bsopia(t_untils *untils, t_cttb *cttb)
{
	bsopia_func(cttb->commands, 0, untils);
	ft_lstclear_command(&cttb->commands);
	return (0);
}
