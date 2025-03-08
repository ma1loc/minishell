#include "../../srcs/mini_shell.h"

void	get_pwd(t_set_env *built_in)
{
	char	buf_path[PATH_MAX];
	char	*path;

	path = getcwd(buf_path, sizeof(buf_path));
	if (path)
		built_in->pwd = ft_strdup(path);
	else
		perror("pwd");
}

void	get_oldpwd(t_set_env *built_in)
{
	char	buf_path[PATH_MAX];
	char	*path;

	path = getcwd(buf_path, sizeof(buf_path));
	if (path)
		built_in->oldpwd = ft_strdup(path);
	else
		perror("pwd");
}

void	pwd_cmd(t_set_env *built_in)
{
	get_pwd(built_in);
	printf("%s\n", built_in->pwd);
}
