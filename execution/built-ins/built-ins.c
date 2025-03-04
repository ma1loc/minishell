#include "../../srcs/mini_shell.h"

void	exit_cmd(char *input)
{
	if (ft_strncmp(input, "exit", 4) == 0)
		exit(0);
}

void	env_cmd(char *input, char **env)
{
	int	i;

	i = 0;
	if (ft_strncmp(input, "env", 3) == 0)
	{
		while (*env)
			printf("%s\n", *env++);
	}
}
