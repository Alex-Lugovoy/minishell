#include "minishell.h"

static int	count_word(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

void	print_env(char **cp_env)
{
	int	i;

	i = 0;
	while (cp_env[i] != NULL)
	{
		if (ft_strchr(cp_env[i], '='))
		{
			write(1, cp_env[i], ft_strlen_b(cp_env[i]));
			write(1, "\n", 1);
			i++;
		}
		else
			i++;
	}
}

char	**sort_mass(char **str)
{
	int		i;
	char	*buf;
	int		k;

	k = count_word(str);
	while (k - 1)
	{
		i = 0;
		while (str[i] != NULL)
		{
			if (str[i + 1] != NULL && (ft_strcmp(str[i], str[i + 1])) > 0)
			{
				buf = str[i];
				str[i] = str[i + 1];
				str[i + 1] = buf;
			}
			i++;
		}
		k--;
	}
	return (str);
}

void	print_export(char **cp_env, int i, int k)
{
	int	flag;

	cp_env = sort_mass(cp_env);
	while (cp_env[i] != NULL)
	{
		flag = 1;
		write(1, "declare -x ", 11);
		k = 0;
		while (cp_env[i][k] != '\0')
		{
			if (cp_env[i][k] != '\0')
				write(1, &cp_env[i][k], 1);
			if (cp_env[i][k] == '=')
			{
				write(1, "\"", 1);
				flag = 0;
			}
			k++;
		}
		if (flag == 0)
			write(1, "\"", 1);
		write(1, "\n", 1);
		i++;
	}
}
