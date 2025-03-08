#include "../../srcs/mini_shell.h"

void	exit_cmd(t_set_env  *built_in)
{
	// >>> have to free all the allocation here before the exit 
	// exit: numeric argument required
	// exit: too many arguments" and not exit
	
    // if (built_in->cmd->args[1])
	// 	exit(0);
    // else
    printf("%s", built_in->cmd->args[0]);

}