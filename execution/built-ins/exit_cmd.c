#include "mini_shell.h"

void	numeric_error(t_gc *gc)
{
	ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
	gc_destroy(gc);
	exit (SYNTAX_ERROR);
}

int	filter_input(char *str, t_gc *gc, int sign)
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
			numeric_error(gc);
		if (result > 9223372036854775807 && sign == -1)
		{
			exit_status = result * sign;
			if (exit_status < 0)
				numeric_error(gc);
		}
		i++;
	}
	return (result * sign);
}

int	ft_atoi(char *str, t_gc *gc)
{
	int					sign;
	unsigned long		result;
	int					i;
	int					exit_status;

	sign = 1;
	result = 0;
	exit_status = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = filter_input(str + i, gc, sign);
	return (result);
}

void exit_cmd(t_setup *setup, t_gc *gc)
{
    int	input;

	input = 0;
    ft_putstr_fd("exit\n", STDOUT_FILENO);
    if (!setup->cmd->args[1])
        exit(setup->exit_stat);		// >>> NOTE to free before
    else if (setup->cmd->args[2])
    {
        ft_perror(setup, "exit: too many arguments\n", EXIT_FAILURE);
        return;
    }
    else
    {
        if (is_valid_number(setup->cmd->args[1]))
        {
            input = ft_atoi(setup->cmd->args[1], gc);
            exit(input);	// >>> NOTE to free before
        }
        else
			numeric_error(gc);
    }
}
