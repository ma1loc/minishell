#include "../../srcs/mini_shell.h"

void	exit_cmd(t_set_env  *built_in)
{
	// >>> have to free all the allocation here before the exit 
	// exit: numeric argument required
	// exit: too many arguments" and not exit
	
    if (!built_in->cmd->args[1])
		exit(0);
	else if (built_in->cmd->args[2]) // >>> exit status (1) too many arguments
		printf("minishell: exit: too many arguments\n");
	else if (ft_isdigit(built_in->cmd->args[1]) == 0)
	{
		printf("yes is a number\n");
	}
}