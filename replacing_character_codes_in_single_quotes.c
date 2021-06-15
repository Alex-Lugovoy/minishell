#include "minishell.h"

static t_parser	*rrr2(t_parser *current)
{
	if (current->special == 2)
	{
		current = current->next;
		if (current == 0)
			return (0);
		while (current != 0 && current->special != 2
			&& current->back != 0 && current->back->special != 3)
		{
			current = current->next;
		}
		if (current == 0)
			return (0);
		current = current->next;
		if (current == 0)
			return (0);
	}
	return (current);
}

static t_parser	*rrr3(t_parser *current)
{
	if (current->symbol[0] == '\'' && current->special != 0
		&& current->back != 0 && current->back->special != 3)
	{
		current = current->next;
		if (current == 0)
			return (0);
		while (current != 0 && current->special != 1)
		{
			current->special = 0;
			current = current->next;
		}
	}
	if (current->symbol[0] == '\'' && current->special != 0
		&& current->back == 0)
	{
		current = current->next;
		if (current == 0)
			return (0);
		while (current != 0 && current->special != 1)
		{
			current->special = 0;
			current = current->next;
		}
	}
	return (current);
}

t_parser	*replacing_character_codes_in_single_quotes(t_parser *start)
{
	t_parser	*current;

	current = start;
	while (current)
	{
		current = rrr2(current);
		if (current == 0)
			break ;
		current =rrr3(current);
		if (current == 0)
			break ;
		current = current->next;
	}
	return (start);
}
