#include "../../srcs/mini_shell.h"

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
    get_oldpwd(built_in);
    set_env(&built_in->env_list, "OLDPWD", built_in->oldpwd);
    cd(built_in);
    free(built_in->pwd);
    get_pwd(built_in);
    set_env(&built_in->env_list, "PWD", built_in->pwd);
}
