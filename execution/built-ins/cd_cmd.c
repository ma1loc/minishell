#include "../../srcs/mini_shell.h"

void	get_pwd(t_set_env *built_in)
{
	char	buf_path[PATH_MAX];
	char	*path;

	path = getcwd(buf_path, sizeof(buf_path));
	if (path)
	{
		if (built_in->pwd)
			free(built_in->pwd);
		built_in->pwd = ft_strdup(path);
	}
	else
		perror("pwd");
}

// cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
void    cd(t_set_env *built_in)
{
    int     status;
    char    *home;

    home = NULL;
    if (built_in->cmd->args[1] == NULL)
    {
        home = getenv("HOME");
        if (!home)
            return (ft_putstr_fd("cd: 'HOME' not set\n", STDERR_FILENO), (void)0);
        status = chdir(home);
        if (status == -1)
            perror("cd");
    }
    else
    {
        status = chdir(built_in->cmd->args[1]);
        if (status == -1)
            perror("cd");
    }
}

void    cd_cmd(t_set_env *built_in)
{
    if (built_in->oldpwd)
        free(built_in->oldpwd);
    set_env(&built_in->env_list, "OLDPWD", built_in->oldpwd);
    cd(built_in);
    free(built_in->pwd);
    get_pwd(built_in);
    set_env(&built_in->env_list, "PWD", built_in->pwd);
}
