#include "mini_shell.h"

void	exit_cmd(t_setup *built_in)
{
	int input;

    if (!built_in->cmd->args[1])
		exit(built_in->exit_status);	// >>> exit by defulte exit with the exit status of the last command
	else if (built_in->cmd->args[2])
	{
		built_in->exit_status = 1;
		ft_perror("exit: too many arguments\n", FAIL); // >>> use the ft_perror
	}
	else if (ft_isdigit(built_in->cmd->args[1]))
	{
		input = ft_atoi(built_in->cmd->args[1]);
		built_in->exit_status = input;
		exit(input);
	}
	else
	{
		built_in->exit_status = 2;
		ft_perror("exit: numeric argument required\n", STDERR_FILENO);
	}
}
