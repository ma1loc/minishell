/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:38:39 by yanflous          #+#    #+#             */
/*   Updated: 2025/04/23 09:38:41 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"


// int red_heredoc(t_setup *setup, t_tree *tree, t_redirections *redir)
int red_heredoc(t_setup *setup, t_redirections *redir)
{
	int	found;
	int	fd;
	int	i;

	i = 0;
	found = 0;
	while (i < setup->heredoc_counter)
	{
		if (ft_strcmp(setup->heredoc->delim_map[i], redir->file_name) == 0)
		{
			fd = open(setup->heredoc->file_name[i], O_RDONLY);
			if (fd >= 0)
			{
				dup2(fd, STDIN_FILENO);
				close(fd);
				found = 1;
				break ;
			}
		}
		i++;
	}
	if (!found)
		return (ft_perror(setup, "heredoc file not found", EXIT_FAILURE), 1);
	return (0);
}
