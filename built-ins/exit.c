#include "../srcs/mini_shell.h"

// ◦ exit with no options
void	exit_cmd(char *input)
{
	if (ft_strncmp(input, "exit", 4) == 0)
		exit(0);
}