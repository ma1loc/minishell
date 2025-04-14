# include "mini_shell.h"

int	*exit_status()
{
	static int	status;
	return (&status);
}

void	main_sigint(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
	*exit_status() = EXIT_SEGINT;
}

void	do_eof(t_setup *setup)
{
	int	exit_status;

	exit_status = setup->exit_stat;
	// printf("exit_status -> %d\n", exit_status);
	gc_destroy(gc);
	printf("exit\n");
	// printf("exit_status -> %d\n", exit_status);
	exit(exit_status);
}

void heredoc_sigint(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
	gc_destroy(gc);
	exit(EXIT_SEGINT);
}
