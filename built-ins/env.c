#include "../srcs/mini_shell.h"

// ◦ env with no options or arguments
void	env_cmd(char *input, char **env)
{
	int	i;

	i = 0;
	if (ft_strncmp(input, "env", 3) == 0)
	{
		while (*env)
			ft_printf("%s\n", *env++);
	}
}