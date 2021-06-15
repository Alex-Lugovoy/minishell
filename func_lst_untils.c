#include "minishell.h"

void	delete_current_untils(t_untils *current)
{
	if (current != 0)
	{
		ft_free(current->command_ex);
	}
}

t_untils	*init_untils(t_untils *untils)
{
	untils = malloc(sizeof(t_untils));
	untils->flag = 1;
	untils->command_ex = 0;
	untils->env = 0;
	untils->first = 0;
	untils->path = 0;
	untils->status = 0;
	untils->line = 0;
	return (untils);
}
