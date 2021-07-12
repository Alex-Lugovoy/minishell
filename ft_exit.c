#include "minishell.h"

static	int	ft_atoi_long_long(const char *nptr)
{
	int				i;
	long long		j;
	int				minus;

	i = 0;
	j = 0;
	minus = 1;
	while (nptr[i] == ' ' || nptr[i] == ' ' || nptr[i] == '\n'
		|| nptr[i] == '\t' || nptr[i] == '\f'
		|| nptr[i] == '\r' || nptr[i] == '\v')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			minus = (-1);
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		j = (j * 10) + (nptr[i] - 48);
		i++;
	}
	return ((int)(j * minus));
}

void	ft_exit2(t_command *command, t_untils *untils, int error, int i)
{
	if (i == 1)
		printf("exit\n");
	delete_current_parser_for_command_list(command);
	delete_current_untils(untils);
	exit(error);
}

static void	ft_exit_3(t_command *command, t_untils *untils, int error)
{
	if (command->next->command[0] == '-')
	{
		if (ft_strlen(command->next->command)
			> ft_strlen("-9223372036854775808"))
		{
			printf("exit\n%s: numeric argument required\n",
				command->next->command);
			ft_exit2(command, untils, 255, 0);
		}
		else if (ft_strlen(command->next->command)
			== ft_strlen("-9223372036854775808"))
		{
			if (ft_strcmp(command->next->command, "-9223372036854775808") > 0)
			{
				printf("exit\n%s: numeric argument required\n",
					command->next->command);
				ft_exit2(command, untils, 255, 0);
			}
		}
		error = (unsigned char)ft_atoi_long_long(command->next->command);
		printf("exit\n");
		ft_exit2(command, untils, error, 0);
	}
}

static void	ft_exit_4(t_command *command, t_untils *untils, int error)
{
	if (ft_strlen(command->next->command) > ft_strlen("9223372036854775807"))
	{
		printf("exit\n%s: numeric argument required\n", command->next->command);
		ft_exit2(command, untils, 255, 0);
	}
	else if (ft_strlen(command->next->command)
		== ft_strlen("9223372036854775807"))
	{
		if (ft_strcmp(command->next->command, "9223372036854775807") > 0)
		{
			printf("exit\n%s: numeric argument required\n",
				command->next->command);
			ft_exit2(command, untils, 255, 0);
		}
	}
	error = (unsigned char)ft_atoi_long_long(command->next->command);
	ft_exit2(command, untils, error, 0);
}

void	ft_exit(t_command *command, t_untils *untils)
{
	int	error;
	int	i;

	check_name_exit(command, untils, error);
	if (command->next->next == 0)
	{
		i = -1;
		while (command->next->command[++i] != 0)
		{
			if (ft_isalpha(command->next->command[i]))
			{
				printf("exit\n%s: numeric argument required\n",
					command->next->command);
				ft_exit2(command, untils, 255, 0);
			}
		}
		if (command->next->command[0] == '-')
			ft_exit_3(command, untils, error);
		else
			ft_exit_4(command, untils, error);
	}
	check_name_exit_2(command, untils, error);
	if (last(command, untils, error))
		return ;
}
