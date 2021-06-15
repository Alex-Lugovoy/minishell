#include "minishell.h"

t_command	*send_command_to_bsopia(t_untils *untils, t_cttb *cttb)
{
	bsopia_func(cttb->commands, 0, untils);
	ft_lstclear_command(&cttb->commands);
	return (0);
}

static int	command_transmission_to_bsopia3(t_cttb *cttb, t_untils *untils)
{
	cttb->tmp = cttb->end_command;
	cttb->end_command = ft_strjoin(cttb->end_command,
			cttb->string_before_doolar);
	ft_free(cttb->tmp);
	ft_free(cttb->string_before_doolar);
	if (cttb->end_command[0] != '\0' || cttb->current->symbol[0] == '$')
	{
		ft_free(cttb->current->symbol);
		cttb->current->symbol = cttb->end_command;
	}
	if (cttb->current->special_array[0] == 9)
	{
		send_command_to_bsopia(untils, cttb);
	}
	if (cttb->current->symbol[0] != ';')
		ft_lstadd_back_parser(&cttb->commands,
			ft_lstnew_parser(ft_strdup(cttb->current->symbol), 0));
	cttb->current = cttb->current->next;
	return (1);
}

static void	command_transmission_to_bsopia5(t_cttb *cttb, t_untils *untils)
{
	if (cttb->env_tmp[0] == '?')
		cttb->str_from_my_env = ft_strdup("$?+");
	else
		cttb->str_from_my_env = my_get_env(cttb->env_tmp, untils->env);
	if (cttb->str_from_my_env == 0)
		cttb->command_tmp = ft_calloc(1, 1);
	else
		cttb->command_tmp = cttb->str_from_my_env;
	ft_free(cttb->env_tmp);
	cttb->env_tmp = cttb->end_command;
	cttb->end_command = ft_strjoin(cttb->end_command,
			cttb->string_before_doolar);
	ft_free(cttb->env_tmp);
	cttb->env_tmp = cttb->end_command;
	cttb->end_command = ft_strjoin(cttb->end_command, cttb->command_tmp);
	ft_free(cttb->command_tmp);
	ft_free(cttb->env_tmp);
	cttb->i_env = cttb->j_env;
	ft_bzero(cttb->string_before_doolar,
		ft_strlen(cttb->current->symbol) + 1);
	cttb->i_for_str_before_dollar = 0;
}

int	ccmd(t_cttb *cttb)
{
	if (cttb->current->special_array[cttb->j_env] == 0
		|| cttb->current->special_array[cttb->j_env] == 5
		|| cttb->current->symbol[cttb->j_env] == ';'
		|| cttb->current->special_array[cttb->j_env] == 3
		|| (cttb->current->special_array[0] == 2
			&& cttb->current->special_array[cttb->j_env] == 2))
		return (1);
	return (0);
}

static	void	command_transmission_to_bsopia4(t_cttb *cttb, t_untils *untils)
{
	while (cttb->j_env < ft_strlen(cttb->current->symbol))
	{
		if (ccmd(cttb) == 1)
			break ;
		if (cttb->current->symbol[cttb->j_env] == '?')
		{
			cttb->env_tmp[cttb->j_env - cttb->i_env - 1]
				= cttb->current->symbol[cttb->j_env];
			break ;
		}
		if (ft_isdigit (cttb->current->symbol[cttb->j_env]))
		{
			cttb->env_tmp[cttb->j_env - cttb->i_env - 1]
				= cttb->current->symbol[cttb->j_env];
			cttb->j_env++;
			break ;
		}
		cttb->env_tmp[cttb->j_env - cttb->i_env - 1]
			= cttb->current->symbol[cttb->j_env];
		cttb->j_env++;
	}
}

static	void	command_transmission_to_bsopia2(t_cttb *cttb, t_untils *untils)
{
	while (cttb->i_env < ft_strlen(cttb->current->symbol))
	{
		if (cttb->current->special_array[cttb->i_env] == 5 )
		{
			if (cttb->current->special_array[cttb->i_env + 1] != 0)
			{
				cttb->env_tmp = malloc(sizeof(char *)
						* (ft_strlen(cttb->current->symbol) - cttb->i_env) + 1);
				ft_bzero(cttb->env_tmp,
					ft_strlen(cttb->current->symbol) - cttb->i_env + 1);
				cttb->j_env = cttb->i_env + 1;
				cttb->i = 0;
				command_transmission_to_bsopia4(cttb, untils);
				command_transmission_to_bsopia5(cttb, untils);
				continue ;
			}
		}
		if (cttb->i_env < ft_strlen(cttb->current->symbol))
			cttb->string_before_doolar[cttb->i_for_str_before_dollar]
				= cttb->current->symbol[cttb->i_env];
		cttb->i_for_str_before_dollar++;
		cttb->i_env++;
	}
}

t_command	*command_transmission_to_bsopia(
				t_parser *list_of_command, t_untils *untils)
{
	t_cttb	cttb;

	cttb.commands = 0;
	cttb.current = list_of_command;
	while (cttb.current)
	{
		cttb.i_env = 0;
		cttb.end_command = ft_calloc(1, 1);
		cttb.string_before_doolar = ft_calloc(
				ft_strlen(cttb.current->symbol) + 1,
				ft_strlen(cttb.current->symbol) + 1);
		cttb.i_for_str_before_dollar = 0;
		command_transmission_to_bsopia2(&cttb, untils);
		if (command_transmission_to_bsopia3(&cttb, untils) == 0)
			break ;
	}
	if (cttb.commands != 0)
	{
		bsopia_func(cttb.commands, 0, untils);
		ft_lstclear_command(&cttb.commands);
	}
	ft_lstclear_parser2(&list_of_command);
	return (0);
}
