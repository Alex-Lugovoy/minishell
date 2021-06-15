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

static t_history	*slash_e(t_history *tmp, t_untils *untils, t_read_str *rd)
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

static char	*slash_n(t_history *tmp, t_untils *untils, t_read_str *rd)
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

void	backspace_22(t_untils *untils, t_history *tmp, t_read_str *rd)
{
	if (untils->flag_up_down == 1)
	{
		tputs(tgetstr("rc", 0), 1, ft_putchar);
		tputs(tgetstr("ce", 0), 1, ft_putchar);
		if (ft_strlen_b(rd->line) && rd->line)
			rd->line = backspace(rd->line);
		else
			tmp->content = backspace(tmp->content);
		write(1, tmp->content, ft_strlen_b(tmp->content));
		write(1, rd->line, ft_strlen_b(rd->line));
	}
	else
	{
		tputs(tgetstr("rc", 0), 1, ft_putchar);
		tputs(tgetstr("ce", 0), 1, ft_putchar);
		rd->line = backspace(rd->line);
		write(1, rd->line, ft_strlen_b(rd->line));
	}
}

static void	ctr_d(t_read_str *rd)
{
	printf("exit\n");
	ft_free(rd->line);
	exit(0);
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

char	*reading_str(struct termios term, t_history **history, t_untils *untils)
{
	t_history	*tmp;
	t_read_str	rd;
	char		*for_wh;

	tmp = ft_lstnew(NULL);
	ft_lstadd_back(history, tmp);
	untils->flag_up_down = 0;
	rd.line = NULL;
	tmp = step_tmp(tmp);
	for_wh = while_1(untils, tmp, &rd);
	if (for_wh != 0)
		return (for_wh);
	if (g_sig_f == 1)
	{
		write(1, "\n", 1);
		free(rd.line);
		rd.line = 0;
		g_sig_f = 0;
		return (0);
	}
	ft_free(rd.line);
	return (ft_strdup_b(tmp->content));
}

void	test222(t_untils *untils, struct termios *term, struct termios *term2,
	t_history *history)
{
	char	*line;

	line = 0;
	while (1)
	{
		tcsetattr(0, TCSANOW, term);
		tputs("bash $> ", 1, ft_putchar);
		tputs(save_cursor, 1, ft_putchar);
		line = reading_str(*term, &history, untils);
		clear_history(&history);
		untils->fd_in = 99;
		untils->fd_out = 99;
		tcsetattr(0, TCSANOW, term2);
		if (line)
			main_parser(line, untils);
		ft_free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	struct termios	term;
	struct termios	term2;
	char			*term_name;
	t_history		*history;
	t_untils		*untils;

	if (envp == 0)
		exit(1);
	history = NULL;
	untils = init_untils(untils);
	term_name = "xterm-256color";
	tcgetattr(0, &term);
	tcgetattr(0, &term2);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 1;
	signal(SIGINT, signal_c);
	signal(SIGQUIT, SIG_IGN);
	tgetent(0, term_name);
	untils->env = copy_envp(envp, untils->env);
	test222(untils, &term, &term2, history);
}
