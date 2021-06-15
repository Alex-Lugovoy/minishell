#include "minishell.h"

t_history	*slash_e(t_history *tmp, t_untils *untils, t_read_str *rd)
{
	char	b[2];
	char	*temporary;

	read (0, b, 2);
	if (b[0] == '[' && b[1] == 'A')
		tmp = up(untils, tmp, rd);
	if (b[0] == '[' && b[1] == 'B')
		tmp = down(untils, tmp, rd);
	return (tmp);
}

t_history	*while_step(t_history *tmp, t_untils *untils, t_read_str *rd)
{
	while (tmp->back)
	{
		if (tmp->line)
		{
			ft_free(tmp->content);
			tmp->content = ft_strdup_b(tmp->line);
		}
		tmp = tmp->back;
	}
	if (rd->line && untils->flag == 1)
	{
		untils->first = ft_strdup_b(tmp->content);
		untils->flag = 0;
	}
	while (tmp->back)
		tmp = tmp->back;
	return (tmp);
}

char	*slash_n(t_history *tmp, t_untils *untils, t_read_str *rd)
{
	char	*save;
	char	*temporary;

	write(1, "\n", 1);
	save = ft_strjoin_line(tmp->content, rd->line);
	while (tmp->next)
		tmp = tmp->next;
	temporary = tmp->content;
	tmp->content = ft_strdup_b(save);
	ft_free(temporary);
	ft_free(save);
	tmp = while_step(tmp, untils, rd);
	if (tmp->content)
	{
		ft_free(tmp->content);
		tmp->content = ft_strdup_b(untils->first);
	}
	while (tmp->next)
		tmp = tmp->next;
	ft_free(rd->line);
	return (ft_strdup_b(tmp->content));
}
