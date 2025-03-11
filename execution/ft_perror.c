#include "mini_shell.h"

void    ft_exit(int exit_status)
{
    if (exit_status == SUCCESS)
        exit(SUCCESS);
    else if (exit_status == FAIL)
        exit(FAIL);
    else if (exit_status == SYNTAX_ERROR)
        exit(SYNTAX_ERROR);
    else if (exit_status == CMD_NOT_FOUND)
        exit(CMD_NOT_FOUND);
    else if (exit_status == CMD_NOT_EXEC)
        exit(CMD_NOT_EXEC);
}

void    ft_perror(char *msg, int exit_status)
{
    // >>> garbage collector have to create and call here <<<
    if (msg)
        ft_putstr_fd(msg, STDERR_FILENO);
    ft_exit(exit_status);
}