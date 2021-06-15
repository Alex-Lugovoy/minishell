#include "minishell.h"

t_parser	*assigning_symbols_to_command(t_parser *start)
{
	t_parser	*new_start;
	t_parser	*current;
	t_parser	*list_of_command;
	int			*special_array;
	int			j;
	int			i;
	char		*str;

	new_start = start;
	i = 0;
	j = 0;
	list_of_command = 0;
	current = start;
	while (current)
	{
		if (current->special != -1)
			i++;
		if ((current->special == -1 || current->next == 0))
		{
			str = ft_calloc(i + 1, i + 1);
			special_array = ft_calloc(i + 1, i + 1);
			i = 0;
			while (new_start != current)
			{
				if (new_start->special != 1 && new_start->special != 2)
				{
					str[i] = new_start->symbol[0];
					special_array[i] = new_start->special;
					i++;
				}
				new_start = new_start->next;
			}
			if (current->next == 0 && current->special != -1)
			{
				if (new_start->special != 1 && new_start->special != 2)
				{
					str[i] = new_start->symbol[0];
					special_array[i] = new_start->special;
				}
			}
			ft_lstadd_back_parser2(&list_of_command,
				ft_lstnew_parser2(str, 0, special_array));
			i = 0;
			if (new_start != 0)
				new_start = new_start->next;
		}
		current = current->next;
	}
	ft_lstclear_parser2(&start);
	current = list_of_command->next;
	t_parser	*temporary;
	while (current)
	{
		if (current->symbol[0] == '\0')
		{
			temporary = current;
			current = current->next;
			delete_current_parser2(temporary);
			continue ;
		}
		current = current->next;
	}
	return (list_of_command);
}
