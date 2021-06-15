#include "minishell.h"

t_parser	*remove_paired_quotes(t_parser	*start)
{
	t_parser	*tmp;
	t_parser	*tmp2;
	t_parser	*tmp3;
	t_parser	*current;
	int			num_quotes;

	current = start;
	while (current->next)
	{
		num_quotes = 0;
		if (current->symbol[0] == '\'' && current->next->symbol[0] == '\''
			&& current->back != 0 && current->back->special != 3)
		{
			tmp3 = current;
			while (tmp3)
			{
				if (tmp3->symbol[0] == '\"')
					num_quotes++;
				tmp3 = tmp3->back;
			}
			if (num_quotes % 2 == 0)
			{
				tmp = current->next;
				tmp2 = current->back;
				delete_current_parser2(current);
				delete_current_parser2(tmp);
				current = tmp2;
			}
		}
		if (current->symbol[0] == '\"' && current->next->symbol[0]
			== '\"' && current->back != 0 && current->back->special != 3)
		{
			tmp3 = current;
			while (tmp3)
			{
				if (tmp3->symbol[0] == '\'')
					num_quotes++;
				tmp3 = tmp3->back;
			}
			if (num_quotes % 2 == 0)
			{
				tmp = current->next;
				tmp2 = current->back;
				delete_current_parser2(current);
				delete_current_parser2(tmp);
				current = tmp2;
			}
		}
		current = current->next;
		if (current == 0)
			break ;
	}
	return (start);
}
