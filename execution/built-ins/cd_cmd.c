#include "mini_shell.h"

// >>> cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
// >>> have to set the exit status here
// >>> "cd ." to fix
// >>> have to use the stat think so to check if the file exist to put error msg if not depand on the access of the file (no such file vs. not a directory).

void    cd(t_setup *built_in)
{
    int     status;
    char    *home;

    home = NULL;
    if (built_in->cmd->args[1] == NULL)
    {
        home = getenv("HOME");
        if (!home)
            ft_perror("cd: 'HOME' not seting in env\n", FAIL); // >>> exit status (1);
        status = chdir(home);
        if (status == -1)
            perror("cd"); // >>> here call the custem ft_perror just reminder 
    }
    else
    {
        if (strcmp(built_in->cmd->args[1], ".") == 0)
            return ;
        status = chdir(built_in->cmd->args[1]);
        if (status == -1)
            perror("cd"); // >>> here to
    }
}

void    cd_cmd(t_setup *built_in)
{
    char    *pwd;

    pwd = ft_strdup(built_in->pwd);
    // if NULL i know i have to do it just skeep it

    cd(built_in);
    get_pwd(built_in);
    set_env(&built_in->env_list, "PWD", built_in->pwd);
    set_env(&built_in->env_list, "OLDPWD", pwd);
    free(pwd);
}
