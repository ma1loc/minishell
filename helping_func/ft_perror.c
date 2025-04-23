/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:46:54 by yanflous          #+#    #+#             */
/*   Updated: 2025/04/23 11:46:59 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_exit(t_setup *setup, int exit_stat)
{
	if (setup)
	{
		if (exit_stat == EXIT_SUCCESS)
			setup->exit_stat = EXIT_SUCCESS;
		else if (exit_stat == EXIT_FAILURE)
			setup->exit_stat = EXIT_FAILURE;
		else if (exit_stat == SYNTAX_ERROR)
			setup->exit_stat = SYNTAX_ERROR;
		else if (exit_stat == CMD_NOT_FOUND)
			setup->exit_stat = CMD_NOT_FOUND;
		else if (exit_stat == CMD_NOT_EXEC)
			setup->exit_stat = CMD_NOT_EXEC;
		else if (exit_stat == EXIT_SEGINT)
			setup->exit_stat = EXIT_SEGINT;
		else if (exit_stat == EXIT_QUIT)
			setup->exit_stat = EXIT_QUIT;
	}
}

void	ft_perror(t_setup *setup, char *msg, int exit_stat)
{
	if (msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	else
		perror("");
	ft_exit(setup, exit_stat);
}
