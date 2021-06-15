#include "minishell.h"

t_history	*down(t_untils *untils, t_history *tmp, t_read_str *rd)
{
	char	*temporary;

	if (tmp->next)
	{
		untils->flag_up_down = 1;
		tputs(tgetstr("rc", 0), 1, ft_putchar);
		tputs(tgetstr("ce", 0), 1, ft_putchar);
		if (rd->line)
		{
			temporary = tmp->content;
			tmp->content = ft_strjoin_line(tmp->content, rd->line);
			ft_free(rd->line);
			ft_free(temporary);
			rd->line = 0;
		}
		tmp = tmp->next;
		write(1, tmp->content, ft_strlen_b(tmp->content));
	}
	return (tmp);
}

t_history	*up(t_untils *untils, t_history *tmp, t_read_str *rd)
{
	char	*temporary;

	if (tmp->back)
	{
		untils->flag_up_down = 1;
		tputs(tgetstr("rc", 0), 1, ft_putchar);
		tputs(tgetstr("ce", 0), 1, ft_putchar);
		if (rd->line)
		{
			temporary = tmp->content;
			tmp->content = ft_strjoin_line(tmp->content, rd->line);
			ft_free(rd->line);
			ft_free(temporary);
			rd->line = 0;
		}
		tmp = tmp->back;
		write(1, tmp->content, ft_strlen_b(tmp->content));
	}
	return (tmp);
}

t_history	*step_tmp(t_history *tmp)
{
	while (tmp->back)
	{
		if (tmp->line == NULL)
			tmp->line = ft_strdup_b(tmp->content);
		tmp = tmp->back;
	}
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	write_sym(t_read_str *rd, char buff)
{
	write (1, &buff, 1);
	rd->line = ft_strjoin_b(rd->line, &buff);
}

char	*while_1(t_untils *untils, t_history *tmp, t_read_str *rd)
{
	char	buff[5];

	while (1)
	{
		if (g_sig_f == 1)
			break ;
		ft_memset(buff, 0, 5);
		read (0, buff, 1);
		if (buff[0] == '\n')
			return (slash_n(tmp, untils, rd));
		else if (buff[0] == '\e')
			tmp = slash_e(tmp, untils, rd);
		else if (buff[0] == '\4' && !(ft_strlen(rd->line))
			&& !(ft_strlen(tmp->content)))
			ctr_d(rd);
		if (!(ft_strcmp(buff, "\177")))
			backspace_22(untils, tmp, rd);
		if ((ft_strcmp(buff, "\177") && buff[0] != '\e'))
		{
			if (ft_isprint(buff[0]))
				write_sym(rd, buff[0]);
		}
	}
	return (0);
}
