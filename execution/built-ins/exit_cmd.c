#include "mini_shell.h"

// >>> to improved litter on
void	exit_cmd(t_setup *setup)
{
	int input;

    if (!setup->cmd->args[1])
		exit(setup->exit_stat);	// >>> exit by defulte exit with the exit status of the last command
	else if (setup->cmd->args[2])
	{
		setup->exit_stat = 1;
		ft_perror(setup, "exit: too many arguments\n", FAIL); // >>> use the ft_perror
	}
	else if (ft_isdigit(setup->cmd->args[1]))
	{
		input = ft_atoi(setup->cmd->args[1]);
		setup->exit_stat = input;
		exit(input);
	}
	else
	{
		setup->exit_stat = 2;
		ft_perror(setup, "exit: numeric argument required\n", STDERR_FILENO);
	}
}
