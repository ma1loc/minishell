/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_msgs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:54:50 by yanflous          #+#    #+#             */
/*   Updated: 2025/04/23 09:54:55 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	allocation_failed_msg(void)
{
	ft_putstr_fd("minishell: Error: memory "\
		"allocation failed.\n", STDERR_FILENO);
	gc_destroy(g_gc);
	exit(EXIT_FAILURE);
}

void	maximum_heredoc_msg(void)
{
	ft_putstr_fd("minishell: maximum here-document "\
		"count exceeded.\n", STDERR_FILENO);
	gc_destroy(g_gc);
	exit(SYNTAX_ERROR);
}

void	do_eof_heredoc(t_setup *setup)
{
	ft_putstr_fd("minishell: warning: here-document "\
	"delimited by end-of-file.\n", STDERR_FILENO);
	cleanup_heredoc(setup);
	gc_destroy(g_gc);
	exit(EXIT_SUCCESS);
}

void	command_not_found(t_setup *setup)
{
	write(STDERR_FILENO, "command not found\n", 18);
	setup->exit_stat = CMD_NOT_FOUND;
}
