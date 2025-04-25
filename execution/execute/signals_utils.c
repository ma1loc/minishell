/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:58:53 by yanflous          #+#    #+#             */
/*   Updated: 2025/04/22 19:58:55 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	main_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	*exit_status() = EXIT_SEGINT;
}

int	*exit_status(void)
{
	static int	status;

	return (&status);
}

void	sigint_exit_status(t_setup *setup)
{
	setup->exit_stat = *exit_status();
	*exit_status() = 0;
}

void	setup_signals(void)
{
	signal(SIGINT, main_sigint);
	signal(SIGQUIT, SIG_IGN);
}
