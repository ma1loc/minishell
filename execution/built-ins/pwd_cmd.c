#include "mini_shell.h"

int	get_pwd(t_setup *setup)
{
    char buf_path[PATH_MAX];
    char *path;
    char *new_pwd;
    
    path = getcwd(buf_path, sizeof(buf_path));
    if (path)
    {
        new_pwd = ft_strdup(path);
        if (!new_pwd)
			allocation_failed_msg();
        if (setup->pwd)
            gc_free(g_gc, setup->pwd);
        setup->pwd = new_pwd;
        setup->exit_stat = 0;
    }
    else
    {
        ft_perror(setup, "pwd: cannot get current directory\n", EXIT_FAILURE);
		return (-1);
    }
	return (0);
}

void	pwd_cmd(t_setup *setup)
{
	if (get_pwd(setup) == 0)
		printf("%s\n", setup->pwd);
}
