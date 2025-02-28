#include "../srcs/mini_shell.h"

// ◦ cd with only a relative or absolute path
// chdir() is a syscall use to change the location of the current path
// like [cd ..] [cd example.txt]

void	cd_cmd_parser(char *input)
{
}

void	cd_cmd(char *input)
{
	int		i;

	if (!input || *input)
		getenv("HOME");
	i = 0;
	while (input[i] && input[i] == ' ')
		i++;
	if (ft_strncmp(&input[i], "cd", 2) == 0)
	{
		input = &input[i + 2];
		i = 0;
		while (input[i] && input[i] == ' ')
			i++;
		if (chdir(&input[i]) == -1)
			perror("cd");
	}
}
