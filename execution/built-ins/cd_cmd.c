#include "../../srcs/mini_shell.h"

// void	get_pwd(t_set_env *built_in)
// {
// 	char	buf_path[PATH_MAX];
// 	char	*path;

// 	path = getcwd(buf_path, sizeof(buf_path));
// 	if (path)
// 	{
// 		if (built_in->pwd)
// 			free(built_in->pwd);
// 		built_in->pwd = ft_strdup(path);
// 	}
// 	else
// 		perror("pwd");
// }

// have to fix (i'm in a dir that have ben deleted and have to do cd .. without any seg or undifind behaver like the bash)
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
            return (ft_putstr_fd("cd: 'HOME' not set\n", STDERR_FILENO), (void)0); // >>> exit status (1);
        status = chdir(home);
        if (status == -1)
            perror("cd");
        else
            set_env(&built_in->env_list, "OLDPWD", built_in->pwd);
    }
    else
    {
        if (strcmp(built_in->cmd->args[1], ".") == 0)
            exit(0);
        status = chdir(built_in->cmd->args[1]);
        if (status == -1)
            perror("cd");
        else
            set_env(&built_in->env_list, "OLDPWD", built_in->pwd);
    }
}

void    cd_cmd(t_set_env *built_in)
{
    cd(built_in);
    get_pwd(built_in);
    set_env(&built_in->env_list, "PWD", built_in->pwd);
}
