#include "mini_shell.h"

int		is_n_option(char *opt)
{
	int	i;

	i = 0;
	if (!opt)
		return (1);
	else if (opt[i] == '-' && opt[i + 1] == '\0')
		return (1);
	else if (opt[i] != '-')
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

// >>> set the exit status to 0 if success <<<
void    echo_cmd(t_setup *setup)
{
	int	i;

	i = 1;
	if (!setup->cmd->args[1])
		printf("\n");
	// >>>>>>>>>>>>>>	just test	>>>>>>>>>>>>>>>>>>
	else if (ft_strcmp(setup->cmd->args[1], "$?") == 0)
		printf("%d\n", setup->exit_stat);
	// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	else if (is_n_option(setup->cmd->args[i]) == 0)
	{
		i = 2;
		while (is_n_option(setup->cmd->args[i]) == 0)
		{
			if (setup->cmd->args[i + 1] == NULL) 
				break;
			i++;
		}
		echo_print(setup->cmd, i);
	}
	else
	{
		echo_print(setup->cmd, i);
		printf("\n");
	}
	setup->exit_stat = 0;
}
