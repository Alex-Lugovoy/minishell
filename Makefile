NAME 	= minishell

DIR 	= .

LIST 	=	backspace.c \
			cd.c command_transmission_to_bsopia.c \
			clear_history.c copy_envp.c echo.c \
			export.c ft_lstadd_back.c ft_lstnew.c \
			ft_lstsize.c ft_strdup.c ft_strjoin_line.c \
			main.c pwd.c unset.c untils_func.c \
			func_lst_tcommand.c check_double_semicolon.c \
			delete_tcommand.c ft_check_command.c \
			ft_perror.c main_parser.c assigning_symbols_to_command.c \
			parse_add_semicolon_to_end.c func_lst_parser.c \
			bsophia_func.c ft_strcmp.c parser_into_list.c \
			check_buildin.c work_pipes.c my_getenv.c \
			assigning_code_to_elements.c remove_paired_quotes.c \
			replacing_character_codes_in_single_quotes.c \
			escaping_characters.c signal.c ft_free.c printf_list.c \
			func_lst_untils.c ft_exit.c replace_dollar_que_into_code.c \
			check_bin.c work_bin.c ft_exit_2.c redirect.c \
			ft_execute_export.c fork_without_pip.c \
			child_without_pip.c children_pip.c \
			check_syntax_error.c

OBJDIR	=	objs/

OBJ 	=	$(LIST:.c=.o)
OBJS	= 	$(addprefix $(OBJDIR), $(OBJ))

FLAGS 	= -Wall -Wextra -Werror -I$(DIR)

CC		= gcc
LIBFTD		= libft/
LIBFT_H		= libft/libft.h
LIBFT_A		= libft.a

LIBS		= $(LIBFTD)$(LIBFT_A)

.c.o:
	$(CC) -c $< -o $(<:.c=.o)

all: lib $(NAME)

lib:
	@make -C $(LIBFTD)

$(NAME): $(OBJS)
		@make -C $(LIBFTD)
		@make -C $(LIBFTD) bonus
		$(CC) -ltermcap -O3 $(OBJS) $(LIBS) -o $(NAME) -lncurses -fsanitize=address

$(OBJDIR)%.o: %.c Makefile
	mkdir -p $(OBJDIR)
	gcc -c $< -o $@
clean:
	rm -f $(OBJS)
	@make -C $(LIBFTD) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFTD) fclean

re: fclean all

.PHONY: all clean fclean re bonus
.SILENT: fclean clean all $(NAME) $(OBJS) $(OBJDIR)
