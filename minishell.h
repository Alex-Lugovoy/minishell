#ifndef MINISHELL_H
# define MINISHELL_H

# include <curses.h>
# include <term.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <errno.h>

int	g_sig_f;

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_NOT_FOUND 127

typedef struct s_untils
{
	char				**env;
	int					flag;
	char				*first;
	int					flag_up_down;
	int					fd_out;
	int					fd_in;
	int					std_in;
	int					std_out;
	char				*command_ex;
	char				*path;
	int					status;
	char				**bin;
	char				**arguments;
	char				*home;
	int					prev_pipe_fds[2];
	int					next_pipe_fds[2];
	int					count_pros;
	char				*line;
	int					flag_n;
}						t_untils;

typedef struct s_history
{
	char				*content;
	char				*line;
	struct s_history	*next;
	struct s_history	*back;
}						t_history;

typedef struct s_helper_parser
{
	int					count_1;
	int					i;
	char				*str;
	int					flag_delete_probel;
	char				*c;
}						t_helper_parser;

typedef struct s_rdqic
{
	char				*start;
	char				*temporary;
	char				*first_part;
	char				*second_part;
	char				*tmp;
}						t_rdqic;

typedef struct s_read_str
{
	char				*line;
	char				*save;
	char				*temporary;
}						t_read_str;

typedef struct s_parser
{
	char				*symbol;
	int					special;
	struct s_parser		*next;
	struct s_parser		*back;
	int					*special_array;
}						t_parser;

typedef struct s_command
{
	char				*command;
	char				*argument;
	char				*flag;
	struct s_command	*next;
	struct s_command	*back;
	int					error;
	char				*redir_right;
	char				*redir_double_right;
	char				*redir_left;
}						t_command;

typedef struct s_cttb
{
	int					i;
	int					i_env;
	int					j_env;
	char				*env_tmp;
	char				*string_before_doolar;
	char				*command_tmp;
	char				*end_command;
	char				*str_from_my_env;
	int					i_for_str_before_dollar;
	char				*tmp;
	t_command			*commands;
	t_parser			*current;
}						t_cttb;

typedef struct s_pil
{
	t_parser		*current;
	t_parser		*start;
	t_command		*check;
	char			*str;
	char			u;
}				t_pil;

typedef struct s_cse
{
	int	i;
	int	_flag;
	int	_flag_pipes;
}		t_cse;

int						ft_strlen_b(char *str);
int						ft_putchar(int c);
char					*ft_strjoin_b(char *s1, char *s2);
t_history				*ft_lstnew(void *content);
void					ft_lstadd_back(t_history **lst, t_history *new);
char					*ft_strdup_b(const char *src);
char					*backspace(char *str);
char					*ft_strjoin_line(char const *s1, char const *s2);
void					clear_history(t_history **history);
int						ft_lstsize(t_history *lst);
void					get_pwd(void);
int						f_echo(char *str, int i);
int						f_cd(t_command *list, t_untils *untils);
char					**copy_envp(char **envp, char **cp_env);
char					**export_add(char **cp_env,
							char *str, t_untils *untils);
char					**f_unset_line(char **cp_env,
							char *str, t_untils *untils);
t_command				*ft_lstnew_parser(void *command, void *flag);
void					ft_lstadd_back_parser(t_command **lst, t_command *new);
void					delete_tcommand(t_command *command);
void					ft_perror(char *error);
void					parse_add_semicolon_to_end(t_command *start);
char					*ft_check_command(char *command);
void					main_parser(char *str, t_untils *untils);
void					bsophia_function(t_command *list, t_untils *untils);
int						ft_lstsize_2(t_command *lst);
void					print_env(char **cp_env);
void					print_export(char **cp_env, int i, int k);
int						check_name(char *str);
int						ft_strcmp(char *str, char *str1);
void					ft_free(void *p);
void					delete_current_untils(t_untils *current);
t_untils				*init_untils(t_untils *untils);
t_command				*parser_into_list(char *str, t_untils *untils);
t_parser				*ft_lstnew_parser2(char *symbol,
							int special, int *special_array);
t_command				*command_transmission_to_bsopia(
							t_parser *list_of_command, t_untils *untils);
t_parser				*assigning_code_to_elements(char *str);
t_parser				*assigning_symbols_to_command(t_parser *start);
t_parser				*remove_paired_quotes(t_parser	*start);
t_parser				*replacing_character_codes_in_single_quotes(
							t_parser *start);
t_parser				*escaping_characters(t_parser *start);
t_parser				*change_escape_code_in_double_quotes(t_parser *start);
void					ft_lstclear_parser2(t_parser **lst);
void					ft_lstclear_command(t_command **lst);
void					ft_lstadd_back_parser2(t_parser **lst, t_parser *new);
void					delete_current_parser2(t_parser *current);
void					delete_current_parser(t_command *current);
void					delete_current_parser_for_command_list(
							t_command *current);
void					ft_lstadd_back_parser2(t_parser **lst, t_parser *new);
t_parser				*ft_lstnew_parser2(char	*symbol,
							int special, int *special_array);
void					bsopia_func(t_command *com, int i, t_untils *untils);
int						check_buildin(char *str);
char					*find_path(t_untils *untils);
int						check_redir(t_command *list, int i, t_untils *untils);
t_command				*redirect_check(t_command *com, t_untils *untils);
int						work_pipes(t_untils *untils, t_command *start);
char					*my_get_env(char *str, char **env);
void					signal_c(int sig_num);
void					signal_slash(int sig_num);
void					printf_command_list(t_command *current);
void					printf_list(t_parser *current);
void					ft_exit(t_command *command, t_untils *untils);
char					*replace_dollar_que_into_code(char *str,
							t_untils *untils);
int						check_bin(char *str);
void					work_bin(t_command *com, t_untils *untils);
void					check_name_exit(t_command *command, t_untils *untils,
							int error);
void					check_name_exit_2(t_command *command, t_untils *untils,
							int error);
void					ft_exit2(t_command *command, t_untils *untils,
							int error);
void					execute_export(t_untils *untils, t_command *list);
void					connect_stdio_to_pipes(int prev_fds[], int next_fds[]);
int						count_pipes(t_command *start);
int						fork_without_pip(t_command *com, t_untils *untils);
void					child_without_pip(t_command *start, t_untils *untils);
void					children_pip(t_command *start, int count_pipes,
							t_untils *untils);
t_command				*check_syntax_error(char *str1, t_untils *untils);
int						last(t_command *command, t_untils *untils, int error);

#endif
