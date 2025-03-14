#include "mini_shell.h"

// >>> cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
// >>> have to set the exit status here
// >>> "cd ." to fix
// >>> have to use the stat think so to check if the file exist to put error msg if not depand on the access of the file (no such file vs. not a directory).
// >>> handle cases where PWD/OLDPWD don't exist in environment





void    cd(t_setup *built_in)
{
    int     status;
    char    *home;

    home = NULL;
    if (built_in->cmd->args[1] == NULL)
    {
        home = getenv("HOME"); // >>> getenv returns a pointer to the environment variable (not dynamically allocated memory),
        if (!home)
            ft_perror("cd: HOME not set\n", FAIL); // >>> exit status (1);
        status = chdir(home);   // >>> to fix litter (no error for no reason)
        if (status == -1)
            perror("cd"); // >>> here call the custem ft_perror just reminder 
    }
    else
    {
        status = chdir(built_in->cmd->args[1]);
        if (status == -1)
            perror("cd"); // >>> here to
    }
}

void    cd_cmd(t_setup *built_in)
{
    char    *pwd;

    pwd = ft_strdup(built_in->pwd);
    if (!pwd)   // >>> if NULL i know i have to do it just skeep it
        ft_perror("cd: memory allocation failed\n", FAIL);
    cd(built_in);
    get_pwd(built_in);
    set_env(&built_in->env_list, "PWD", built_in->pwd);
    set_env(&built_in->env_list, "OLDPWD", pwd);
    free(pwd);
}
