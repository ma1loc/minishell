/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:42:15 by yanflous          #+#    #+#             */
/*   Updated: 2025/04/23 09:42:20 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	red_append(t_setup *setup, t_tree *tree, t_redirections *redirection)
{
	int		app_fd;

	app_fd = open(redirection->file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (app_fd < 0)
		return (ft_perror(setup, NULL, EXIT_FAILURE), -1);
	if (tree->cmd->name == NULL)
		return (close(app_fd), 1);
	else
	{
		if (dup2(app_fd, STDOUT_FILENO) == -1)
			return (ft_perror(setup, NULL, EXIT_FAILURE), -1);
		close(app_fd);
	}
	return (0);
}
