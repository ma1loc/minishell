#include "mini_shell.h"

int	*exit_status()
{
	static int	status;
	
	return (&status);
}

void	sigint_exit_status(t_setup *setup)
{
	setup->exit_stat = *exit_status();
	*exit_status() = 0;
}

void	setup_signals()
{
	signal(SIGINT, main_sigint);
	signal(SIGQUIT, SIG_IGN);
}
