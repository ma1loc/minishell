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

void    cd_cmd(t_setup *setup)
{
    char    *tmp_pwd;
	int		status;

	if (!setup->pwd)
    {
        ft_perror(setup, "cd: current directory not set\n", EXIT_FAILURE);
        return  ;
    }
    tmp_pwd = ft_strdup(setup->pwd);
	if (!tmp_pwd)
		return (ft_perror(setup, "cd: memory allocation failed\n", EXIT_FAILURE), (void)0);
	status = cd(setup);
    if (status == 0)
    {
        if (get_pwd(setup) == 0)
		{
        	set_env(setup, "PWD", setup->pwd);
        	set_env(setup, "OLDPWD", tmp_pwd);
		}
    }
	free(tmp_pwd);
}
