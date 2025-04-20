#include "mini_shell.h"

void	numeric_error()
{
	ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
	gc_destroy(g_gc);
	exit (SYNTAX_ERROR);
}

int	filter_input(char *str, int sign)
{
	int				i;
	unsigned long	result;
	int				exit_status;

	i = 0;
	result = 0;
	exit_status = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > 9223372036854775807 && sign == 1)
			numeric_error();
		if (result > 9223372036854775807 && sign == -1)
		{
			exit_status = result * sign;
			if (exit_status < 0)
				numeric_error();
		}
		i++;
	}
	return (result * sign);
}

int	a_to_i(char *str)
{
	int					sign;
	unsigned long		result;
	int					i;

	sign = 1;
	result = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = filter_input(str + i, sign);
	return (result);
}

void	exiting(t_setup *setup)
{
    int	input;

	input = 0;
	if (is_valid_number(setup->cmd->args[1]))
    {
        input = a_to_i(setup->cmd->args[1]);
		gc_destroy(g_gc);
		exit(input);
    }
    else
		numeric_error();
}

void	exit_cmd(t_setup *setup)
{
	int	exit_status;

	exit_status = 0;
	exit_status = setup->exit_stat;
    ft_putstr_fd("exit\n", STDOUT_FILENO);
    if (!setup->cmd->args[1])
	{
		gc_destroy(g_gc);
        exit(exit_status);	
	}
    else if (setup->cmd->args[2])
    {
        ft_perror(setup, "exit: too many arguments\n", EXIT_FAILURE);
        return ;
    }
    else
		exiting(setup);
}
