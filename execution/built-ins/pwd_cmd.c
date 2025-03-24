#include "mini_shell.h"

void	get_pwd(t_setup *setup)
{
	char	buf_path[PATH_MAX];
	char	*path;

	path = getcwd(buf_path, sizeof(buf_path));
	if (path)
	{
		if (setup->pwd)
			free(setup->pwd);
		setup->pwd = ft_strdup(path);
	}
	else
		ft_perror(setup, "pwd", EXIT_FAILURE); // >>> update with ft_perror
}

void	pwd_cmd(t_setup *setup)
{
	get_pwd(setup);
	printf("%s\n", setup->pwd);
}
