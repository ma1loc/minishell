#include "../../srcs/mini_shell.h"

void	pwd_cmd()
{
	char	buf_path[PATH_MAX];
	char	*path;

	path = getcwd(buf_path, sizeof(buf_path));
	if (path)
	{
		ft_putstr_fd(path, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else
		perror("pwd");
}
