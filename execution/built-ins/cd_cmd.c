#include "mini_shell.h"

// >>> cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
// >>> have to set the exit status here
// >>> "cd ." to fix
// >>> have to use the stat think so to check if the file exist to put error msg if not depand on the access of the file (no such file vs. not a directory).
// >>> handle cases where PWD/OLDPWD don't exist in environment
// >>> to inproved litter on.
void    cd(t_setup *setup)
{
    int     status;
    char    *home;

    home = NULL;
    if (setup->cmd->args[1] == NULL)
    {
        home = getenv("HOME"); // >>> getenv returns a pointer to the environment variable (not dynamically allocated memory),
        if (!home)
            ft_perror(setup, "cd: HOME not set\n", FAIL); // >>> exit status (1);
        status = chdir(home);   // >>> to fix litter (no error for no reason)
        if (status == -1)
            perror("cd"); // >>> here call the custem ft_perror just reminder 
    }
    else
    {
        status = chdir(setup->cmd->args[1]);
        if (status == -1)
            perror("cd"); // >>> here to
    }

}

void    cd_cmd(t_setup *setup)
{
    char    *pwd;

    pwd = ft_strdup(setup->pwd);
    if (!pwd)   // >>> if NULL i know i have to do it just skeep it
    {
        // if (cd(setup)); // check if the cd success.
        // {
            cd(setup);
            get_pwd(setup);
            set_env(&setup->env, "PWD", setup->pwd);
            set_env(&setup->env, "OLDPWD", pwd);
            free(pwd);
        // }
    }
    else
        ft_perror(setup, "cd: memory allocation failed\n", FAIL);
}
