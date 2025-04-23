/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:48:42 by yanflous          #+#    #+#             */
/*   Updated: 2025/04/23 09:48:44 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	red_output(t_setup *setup, t_tree *tree, t_redirections *redirection)
{
	int	out_fd;

	out_fd = open(redirection->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd < 0)
		return (ft_perror(setup, NULL, EXIT_FAILURE), -1);
	if (tree->cmd->name == NULL)
		return (close(out_fd), 1);
	else
	{
		if (dup2(out_fd, STDOUT_FILENO) == -1)
			return (close(out_fd), ft_perror(setup, NULL, EXIT_FAILURE), -1);
		close(out_fd);
	}
	return (0);
}
