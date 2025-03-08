#include "../../srcs/mini_shell.h"

int		is_option(char	*opt)
{
	int	i;

	i = 0;
	if (opt[i] != '-')
		return (1);
	else
		i++;
	while (opt[i])
	{
		if (opt[i] == 'n')
			i++;
		else
			return (1);
	}
	return (0);
}

void	echo_print(t_command *cmd, int i)
{
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1] != NULL)
			printf(" ");
		i++;
	}
}

void    echo_cmd(t_set_env *built_in)
{
	int	i;

	i = 1;
	if (!built_in->cmd->args[1])
		printf("\n");
	else if (is_option(built_in->cmd->args[i]) == 0)
	{
		i = 2;
		echo_print(built_in->cmd, i);
	}
	else
	{
		echo_print(built_in->cmd, i);
		printf("\n");
	}
}
