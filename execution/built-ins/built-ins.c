#include "../../srcs/mini_shell.h"

void	pwd_cmd(char *input)
{
	char	path[1024];
	char	*pwd;

	pwd = NULL;
	if (ft_strncmp(input, "pwd", 3) == 0)
	{
		pwd = getcwd(path, sizeof(path));
		if (pwd)
		{
			pwd = ft_strjoin(path, "\n");
			ft_putstr_fd(pwd, 1);
			free(pwd);
		}
		else
			perror("pwd:");
    }
}

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
