#include "minishell.h"

char	*backspace(char *str)
{
	int		i;
	char	*n_str;
	int		k;

	k = 0;
	i = 0;
	i = ft_strlen(str);
	if (i == 0)
	{
		ft_free(str);
		return (0);
	}
	n_str = malloc(i);
	while (k < i - 1)
	{
		n_str[k] = str[k];
		k++;
	}
	n_str[k] = '\0';
	ft_free(str);
	return (n_str);
}
