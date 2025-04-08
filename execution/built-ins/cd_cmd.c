#include "mini_shell.h"

int	cd(t_setup *setup)
{
    int     status;
    char    *home;

	home = NULL;
    if (setup->cmd->args[1] == NULL)
    {
        home = getenv("HOME");
        if (!home)
			return (ft_perror(setup, "cd: HOME not set\n", EXIT_FAILURE), -1);
        status = chdir(home);
        if (status == -1)
            return (ft_perror(setup, NULL, EXIT_FAILURE), -1); // the cu
    }
    else
    {
        status = chdir(setup->cmd->args[1]);
        if (status == -1)
			return (ft_perror(setup, NULL, EXIT_FAILURE), -1); // >>> here to
    }
	return (0);
}

void    cd_cmd(t_setup *setup, t_gc *gc)
{
    char    *tmp_pwd;
	int		status;

	if (!setup->pwd)
    {
        ft_perror(setup, "cd: current directory not set\n", EXIT_FAILURE);
        return ;
    }
    tmp_pwd = ft_strdup(setup->pwd, gc);
	if (!tmp_pwd)
		allocation_failed_msg(gc);
	status = cd(setup);
    if (status == 0)
    {
        if (get_pwd(setup, gc) == 0)
		{
        	// set_env(setup, "PWD", setup->pwd);
        	update_env(setup, "PWD", setup->pwd, gc);
        	// set_env(setup, "OLDPWD", tmp_pwd);
        	update_env(setup, "OLDPWD", tmp_pwd, gc);
		}
    }
	gc_free(gc, tmp_pwd);
}
