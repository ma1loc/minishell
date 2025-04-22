#include "mini_shell.h"

void    ft_exit(t_setup *setup, int exit_stat)
{
    if (setup)
    {
        if (exit_stat == EXIT_SUCCESS)				// >>> exit 0
        setup->exit_stat = EXIT_SUCCESS;
        else if (exit_stat == EXIT_FAILURE)			// >>> exit 1
            setup->exit_stat = EXIT_FAILURE;
        else if (exit_stat == SYNTAX_ERROR)   		// >>> exit 2
            setup->exit_stat = SYNTAX_ERROR;
        else if (exit_stat == CMD_NOT_FOUND)		// >>> exit 127
            setup->exit_stat = CMD_NOT_FOUND;
        else if (exit_stat == CMD_NOT_EXEC)			// >>> exit 126
            setup->exit_stat = CMD_NOT_EXEC;
		else if (exit_stat == EXIT_SEGINT)
			setup->exit_stat = EXIT_SEGINT;
		else if (exit_stat == EXIT_QUIT)
			setup->exit_stat = EXIT_QUIT;
    }
}

void    ft_perror(t_setup *setup, char *msg, int exit_stat)
{
    if (msg)
        ft_putstr_fd(msg, STDERR_FILENO);
    else
        perror("");
    ft_exit(setup, exit_stat);
}
