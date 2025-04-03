#include "mini_shell.h"

void exit_cmd(t_setup *setup)
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
            exit(input);	// >>> NOTE to free before
        }
        else
		{
            ft_perror(setup, "exit: numeric argument required\n", SYNTAX_ERROR);
			exit (SYNTAX_ERROR);	// >>> NOTE to free before
		}
    }
}
