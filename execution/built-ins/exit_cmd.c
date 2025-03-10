#include "../../srcs/mini_shell.h"

void	exit_cmd(t_set_env  *built_in)
{
	int input;

    if (!built_in->cmd->args[1])
		exit(built_in->exit_status);
	else if (built_in->cmd->args[2])
	{
		built_in->exit_status = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	}
	else if (ft_isdigit(built_in->cmd->args[1]) == 0)
	{
		input = ft_atoi(built_in->cmd->args[1]);
		built_in->exit_status = input;
		exit(input);
	}
	else
	{
		built_in->exit_status = 2;
		ft_putstr_fd("minishell: exit: numeric argument required\n", STDERR_FILENO);
	}
}
