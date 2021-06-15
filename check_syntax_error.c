#include "minishell.h"

static t_command	*cser(char *str1, t_untils *untils)
{
	untils->status = 258;
	return (ft_lstnew_parser(str1, 0));
}

static t_command	*check_syntax_error4(char *str1,
	t_untils *untils, int i, int _flag)
{
	while (i < ft_strlen(str1))
	{
		if (str1[i] == '\"' || str1[i] == '\'')
			_flag++;
		if (str1[i] == '|' && _flag % 2 == 0)
		{
			i++;
			if (i >= ft_strlen(str1))
				break ;
			while (str1[i] == ' ')
				i++;
			if (i < ft_strlen(str1) && str1[i] == '|')
			{
				i++;
				if (i >= ft_strlen(str1))
					break ;
				while (str1[i] == ' ')
					i++;
				if (i < ft_strlen(str1) && str1[i] == '|')
					return (cser("syntax error near `|'", untils));
			}
		}
		i++;
	}
	return (0);
}

static t_command	*check_syntax_error3(char *str1, t_untils *untils, int i)
{
	t_cse	cse;

	cse._flag_pipes = 0;
	cse._flag = 0;
	while (i < ft_strlen(str1))
	{
		if (str1[i] == '|' && cse._flag_pipes == 0)
			return (cser("syntax error near unexpected token '|'", untils));
		if (str1[i] != '|' && str1[i] != ' ')
			cse._flag_pipes = 1;
		if (str1[i] == '\"' || str1[i] == '\'')
			cse._flag++;
		if (str1[i] == ';' && cse._flag % 2 == 0)
		{
			i++;
			if (i >= ft_strlen(str1))
				break ;
			while (str1[i] == ' ')
				i++;
			if (i < ft_strlen(str1) && str1[i] == ';')
				return (cser("syntax error near `;;'", untils));
		}
		i++;
	}
	return (0);
}

static t_command	*check_syntax_error2(char *str1,
	t_untils *untils, int i, int _flag)
{
	if (str1[ft_strlen(str1) - 1] == '>' || str1[ft_strlen(str1) - 1] == '<')
		return (cser("syntax error near unexpected token `\\n'", untils));
	i = ft_strlen(str1) - 1;
	while (i > -1)
	{
		if (str1[i] != ' ' && str1[i] != '|')
			_flag = 1;
		if (str1[i] == '|' && _flag == 0)
			return (cser("syntax error near unexpected token `|'", untils));
		i--;
	}
	_flag = 0;
	i = 0;
	while (str1[i])
	{
		if (str1[i] != ' ' && str1[i] != ';')
			_flag = 1;
		if (str1[i] == ';' && _flag == 0)
			return (cser("syntax error near unexpected token `;'", untils));
		if (str1[i] == ';' && _flag == 1)
			_flag = 0;
		i++;
	}
	return (0);
}

t_command	*check_syntax_error(char *str1, t_untils *untils)
{
	t_command	*check;

	check = check_syntax_error2(str1, untils, 0, 0);
	if (check != 0)
		return (check);
	check = check_syntax_error3(str1, untils, 0);
	if (check != 0)
		return (check);
	check = check_syntax_error4(str1, untils, 0, 0);
	if (check != 0)
		return (check);
	return (0);
}
