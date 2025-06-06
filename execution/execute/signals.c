/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:06:48 by yanflous          #+#    #+#             */
/*   Updated: 2025/04/22 14:06:50 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	execute_sigint(int sig)
{
	(void)sig;
	gc_destroy(g_gc);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	exit(EXIT_SEGINT);
}

t_setup	**get_setup(void)
{
	static t_setup	*setup_ptr;

	return (&setup_ptr);
}

void	heredoc_sigint(int sig)
{
	t_setup	*setup;

	(void)sig;
	setup = *get_setup();
	write(STDOUT_FILENO, "\n", 1);
	if (setup != NULL)
		cleanup_heredoc(setup);
	gc_destroy(g_gc);
	exit(EXIT_SEGINT);
}

void	do_eof(t_setup *setup)
{
	int	exit_stat;

	exit_stat = setup->exit_stat;
	gc_destroy(g_gc);
	printf("exit\n");
	exit(exit_stat);
}

void	signal_status(t_setup *setup, int status)
{
	if (WIFEXITED(status))
		setup->exit_stat = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		setup->exit_stat = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", STDERR_FILENO);
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	}
}
