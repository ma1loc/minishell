#include "../srcs/mini_shell.h"

// ◦ pwd with no options
// getcwd is a func (not syscall!!!) that get the current path your in.
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