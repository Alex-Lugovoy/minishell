#include "minishell.h"

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

void	ctr_d(t_read_str *rd)
{
	printf("exit\n");
	ft_free(rd->line);
	exit(0);
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
