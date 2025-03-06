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

void    echo_cmd(t_command *cmd)
{
	int	i;

	i = 1;
	if (is_option(cmd->args[i]) == 0)
	{
		i = 2;
		while (cmd->args[i])
		{
			printf("%s", cmd->args[i]);
			i++;
		}
	}
	else
	{
		while (cmd->args[i])
		{
			printf("%s", cmd->args[i]);
			i++;
		}
		printf("\n");
	}
}
