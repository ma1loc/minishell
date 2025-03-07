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
            perror("cd: 'HOME' not set\n");
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
    cd(built_in);
    get_pwd(built_in);
}
