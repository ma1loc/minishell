#include "mini_shell.h"

void    ft_exit(t_setup *setup, int exit_stat)
{
    if (exit_stat == SUCCESS)             // >>> exit 0
        setup->exit_stat = SUCCESS;
    else if (exit_stat == FAIL)           // >>> exit 1
        setup->exit_stat = FAIL;
    else if (exit_stat == SYNTAX_ERROR)   // >>> exit 2
        setup->exit_stat = SYNTAX_ERROR;
    else if (exit_stat == CMD_NOT_FOUND)  // >>> exit 127
        setup->exit_stat = CMD_NOT_FOUND;
    else if (exit_stat == CMD_NOT_EXEC)   // >>> exit 126
        setup->exit_stat = CMD_NOT_EXEC;
    // else
    //     setup->exit_stat = exit_stat;
}

void    ft_perror(t_setup *setup, char *msg, int exit_stat)
{
    // >>> garbage collector have to create and call here <<<
    if (msg)
        ft_putstr_fd(msg, STDERR_FILENO);
    ft_exit(setup, exit_stat);
}