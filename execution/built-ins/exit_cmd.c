#include "mini_shell.h"

int	ft_atoi(const char *str)
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
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > 9223372036854775807 && sign == 1)
			return (-1);
		if (result > 9223372036854775807 && sign == -1)
			return (0);
		i++;
	}
	return (result * sign);
}

// handel the max int 9223372036854775807
// if > 9223372036854775807 -> numeric argument required
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
            input = ft_atoi(setup->cmd->args[1]);
			gc_destroy(gc);
            exit(input);	// >>> NOTE to free before
        }
        else
		{
            ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
			gc_destroy(gc);
			exit (SYNTAX_ERROR);	// >>> NOTE to free before
		}
    }
}
