#include "minishell.h"

t_parser	*change_escape_code_in_double_quotes(t_parser *start)
{
	t_parser	*current;

	current = start;
	while (current)
	{
		if (current->special == 2)
		{
			current = current->next;
			if (current == 0)
				break ;
			while (current->special != 2)
			{
				if (current->special == -1)
					current->special = 0;
				current = current->next;
			}
		}
		current = current->next;
	}
	return (start);
}

t_parser	*escaping_characters(t_parser *start)
{
	t_parser	*current;
	t_parser	*next;
	int			quotes;

	current = start;
	quotes = 0;
	while (current->next)
	{
		if (current->symbol[0] == '\"')
			quotes++;
		if (current->special == 5)
			if (current->next != 0 && current->next->symbol[0] == '\\')
				current->special = 0;
		if (current->symbol[0] == '\\' && current->special != 0
			&& (current->next->special != 7 || quotes % 2 == 0))
		{
			if (current->back == 0)
				start = current->next;
			next = current->next;
			delete_current_parser2(current);
			next->special = 0;
		}
		current = current->next;
	}
	return (start);
}
