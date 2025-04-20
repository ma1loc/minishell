#include "mini_shell.h"

void	set_pipe(t_setup *setup, int *fd)
{
    if (pipe(fd) == -1)
    {
        ft_perror(setup, NULL, EXIT_FAILURE);
        return;
    }
}

pid_t	set_fork(t_setup *setup)
{
	pid_t	pid;

	pid = 0;
	if (setup->fork_flag)
	{
		pid = fork();
		if (pid == -1)
		{
			ft_perror(setup, NULL, EXIT_FAILURE);
			gc_destroy(g_gc);
			exit(EXIT_FAILURE);
		}
	}
	return (pid);
}

pid_t	set_first_fork(t_setup  *setup, int *fd)
{
    pid_t pid1;

    pid1 = fork();
    if (pid1 < 0)
    {
        close(fd[0]);
        close(fd[1]);
        ft_perror(setup, NULL, EXIT_FAILURE);
        return (-1);
    }
    return (pid1);
}

pid_t	set_second_fork(t_setup  *setup, pid_t pid_1, int *fd)
{
    pid_t   pid_2;
    
    pid_2 = fork();
    if (pid_2 < 0)
    {
        close(fd[0]);
        close(fd[1]);
        waitpid(pid_1, NULL, 0);  // >>> wait for first child
        ft_perror(setup, NULL, EXIT_FAILURE);
        return (-1);
    }
    return (pid_2);
}
