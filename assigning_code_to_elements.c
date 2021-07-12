#include "minishell.h"

static	t_parser	*helper_function4(t_parser *start,
	t_helper_parser *help, char *str)
{
	if (help->i + 1 < ft_strlen(str) && str[help->i + 1] == '>')
	{
		ft_lstadd_back_parser2(&start,
			ft_lstnew_parser2(ft_strdup(" "), -1, 0));
		ft_lstadd_back_parser2(&start, ft_lstnew_parser2(help->c, 29, 0));
		help->c = ft_calloc(2, 2);
		help->c[0] = '>';
		ft_lstadd_back_parser2(&start, ft_lstnew_parser2(help->c, 29, 0));
		ft_lstadd_back_parser2(&start,
			ft_lstnew_parser2(ft_strdup(" "), -1, 0));
		help->i += 1;
	}
	else
	{
		ft_lstadd_back_parser2(&start,
			ft_lstnew_parser2(ft_strdup(" "), -1, 0));
		ft_lstadd_back_parser2(&start, ft_lstnew_parser2(help->c, 19, 0));
		ft_lstadd_back_parser2(&start,
			ft_lstnew_parser2(ft_strdup(" "), -1, 0));
	}
	return (start);
}

static	t_parser	*helper_function3(t_parser *start,
	t_helper_parser *help, char *str)
{
	if (str[help->i] == '\"')
	{
		help->count_1 += 1;
		ft_lstadd_back_parser2(&start, ft_lstnew_parser2(help->c, 2, 0));
	}
	else if (str[help->i] == '\'')
	{
		help->count_1 += 1;
		ft_lstadd_back_parser2(&start, ft_lstnew_parser2(help->c, 1, 0));
	}
	else if (str[help->i] == '<' && help->count_1 % 2 == 0)
	{
		ft_lstadd_back_parser2(&start,
			ft_lstnew_parser2(ft_strdup(" "), -1, 0));
		ft_lstadd_back_parser2(&start, ft_lstnew_parser2(help->c, 18, 0));
		ft_lstadd_back_parser2(&start,
			ft_lstnew_parser2(ft_strdup(" "), -1, 0));
	}
	else if (str[help->i] == '>' && help->count_1 % 2 == 0)
	{
		start = helper_function4(start, help, str);
	}
	else
		ft_lstadd_back_parser2(&start, ft_lstnew_parser2(help->c, 7, 0));
	return (start);
}

static	t_parser	*helper_function2(t_parser *start,
	t_helper_parser *help, char *str)
{
	if (str[help->i] == '?')
		ft_lstadd_back_parser2(&start, ft_lstnew_parser2(help->c, 4, 0));
	else if (str[help->i] == '$')
		ft_lstadd_back_parser2(&start, ft_lstnew_parser2(help->c, 5, 0));
	else if (str[help->i] == ' ')
		ft_lstadd_back_parser2(&start, ft_lstnew_parser2(help->c, -1, 0));
	else if (str[help->i] == ';' && help->count_1 % 2 == 0)
	{
		ft_lstadd_back_parser2(&start,
			ft_lstnew_parser2(ft_strdup(" "), -1, 0));
		ft_lstadd_back_parser2(&start, ft_lstnew_parser2(help->c, 9, 0));
		ft_lstadd_back_parser2(&start,
			ft_lstnew_parser2(ft_strdup(" "), -1, 0));
	}
	else if (str[help->i] == '|' && help->count_1 % 2 == 0)
	{
		ft_lstadd_back_parser2(&start,
			ft_lstnew_parser2(ft_strdup(" "), -1, 0));
		ft_lstadd_back_parser2(&start, ft_lstnew_parser2(help->c, 20, 0));
		ft_lstadd_back_parser2(&start,
			ft_lstnew_parser2(ft_strdup(" "), -1, 0));
	}
	else
		start = helper_function3(start, help, str);
	return (start);
}

static t_parser	*helper_function1(t_parser *start,
	t_helper_parser *help, char *str)
{
	if (str[help->i] == '\\')
		ft_lstadd_back_parser2(&start, ft_lstnew_parser2(help->c, 3, 0));
	else if ((help->i + 2) < ft_strlen(str) && ((str[help->i] == '\"'
				&& str[help->i + 2] == '\"') || (str[help->i] == '\''
				&& str[help->i + 2] == '\'')) && str[help->i + 1] != '\"'
		&& str[help->i + 1] != '\'' && str[help->i + 1] != ' ')
	{
		help->c[0] = str[help->i + 1];
		if (str[help->i + 1] == '$')
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(help->c, 5, 0));
		else if (str[help->i + 1] == '\\')
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(help->c, 3, 0));
		else if (str[help->i + 1] == '?')
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(help->c, 4, 0));
		else
			ft_lstadd_back_parser2(&start, ft_lstnew_parser2(help->c, 7, 0));
		help->i += 2;
	}
	else
		start = helper_function2(start, help, str);
	return (start);
}

t_parser	*assigning_code_to_elements(char *str)
{
	t_parser		*start;
	t_helper_parser	help;

	help.i = 0;
	help.count_1 = 0;
	start = 0;
	help.flag_delete_probel = 0;
	while (help.i < ft_strlen(str))
	{
		if (str[help.i] == ' ' && !help.flag_delete_probel)
		{
			help.i += 1;
			continue ;
		}
		help.c = malloc(sizeof(char) * 2);
		ft_bzero(help.c, 2);
		help.c[0] = str[help.i];
		start = helper_function1(start, &help, str);
		help.flag_delete_probel = 1;
		help.c = 0;
		help.i += 1;
	}
	return (start);
}
