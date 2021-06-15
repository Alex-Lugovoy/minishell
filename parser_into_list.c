#include "minishell.h"

static t_command	*check_quotes(t_parser *start, t_untils *untils)
{
	t_parser	*current;
	int			count;
	int			count_double;

	count = 0;
	count_double = 0;
	current = start;
	while (current)
	{
		if (current->symbol[0] == '\'' && current->special != 0
			&& count_double % 2 == 0)
			count++;
		if (current->symbol[0] == '\"' && current->special != 0
			&& count % 2 == 0)
			count_double++;
		current = current->next;
	}
	if (count % 2 != 0 || count_double % 2 != 0)
	{
		ft_lstclear_parser2(&start);
		untils->status = 1;
		return (ft_lstnew_parser("error with quotes", 0));
	}
	return (0);
}

static t_command	*parser_into_list2(t_parser *start, t_untils *untils)
{
	t_parser	*current;
	t_parser	*list_of_command;

	list_of_command = assigning_symbols_to_command(start);
	current = list_of_command;
	while (current)
	{
		if (current->symbol[0] == '>' || current->symbol[0] == '<')
		{
			if (current->next && (current->next->symbol[0] == '>'
					|| current->next->symbol[0] == '<'
					|| current->next->symbol[0] == ' '
					|| current->next->symbol[0] == ';'
					|| current->next->symbol[0] == '|'))
				return (ft_lstnew_parser("error near `>' or '<' or '>>'", 0));
		}
		current = current->next;
	}
	if (list_of_command->symbol[0] == '\0')
	{
		current = list_of_command;
		list_of_command = list_of_command->next;
		delete_current_parser2(current);
	}
	current = list_of_command;
	while (current->next)
		current = current->next;
	if (current->symbol[0] == ';')
		delete_current_parser2(current);
	return (command_transmission_to_bsopia(list_of_command, untils));
}

static void	parser_into_list3_33(t_parser *start, t_parser *current)
{
	current = start;
	while (current)
	{
		if (current->symbol[0] == '\"' && current->back != 0
			&& current->back->symbol[0] != '\\')
		{
			current = current->next;
			while (current != 0)
			{
				if (current->symbol[0] == '\"'
					&& current->back->symbol[0] != '\\')
					break ;
				if (current->special == 1)
					current->special = 0;
				current = current->next;
			}
		}
		if (current == 0)
			break ;
		current = current->next;
	}
}

static t_command	*parser_into_list3(t_parser *start,
	t_parser *current, t_command	*check, t_untils *untils)
{
	parser_into_list3_33(start, current);
	start = replacing_character_codes_in_single_quotes(start);
	start = escaping_characters(start);
	check = check_quotes(start, untils);
	if (check != 0)
		return (check);
	start = change_escape_code_in_double_quotes(start);
	return (parser_into_list2(start, untils));
}

t_command	*parser_into_list(char *str1, t_untils *untils)
{
	t_pil	pil;

	if (str1 == 0 || str1[0] == '\0' || str1[0] == '\n')
		return (0);
	pil.check = check_syntax_error(str1, untils);
	if (pil.check != 0)
		return (pil.check);
	pil.str = ft_strdup(str1);
	pil.start = assigning_code_to_elements(pil.str);
	ft_free(pil.str);
	pil.current = pil.start;
	while (pil.current)
	{
		if (pil.current->symbol[0] == '\\' && pil.current->next == 0)
		{
			pil.u = ' ';
			ft_lstadd_back_parser2(&pil.start,
				ft_lstnew_parser2(ft_strdup(&pil.u), -1, 0));
		}
		pil.current = pil.current->next;
	}
	pil.start = remove_paired_quotes(pil.start);
	parser_into_list3(pil.start, 0, 0, untils);
	return (0);
}
