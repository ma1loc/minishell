#include "mini_shell.h"

// >>> cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
// >>> have to set the exit status here
// >>> "cd ." to fix
void    cd(t_setup *built_in)
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

void    cd_cmd(t_setup *built_in)
{
    cd(built_in);
    get_pwd(built_in);
    set_env(&built_in->env_list, "PWD", built_in->pwd);
}
