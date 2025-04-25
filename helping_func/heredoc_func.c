/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:00:06 by yanflous          #+#    #+#             */
/*   Updated: 2025/04/23 10:00:12 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	heredoc_counter_in_pipe(t_setup *setup, t_tree *tree)
{
	if (tree->left)
		heredoc_counter(setup, tree->left);
	if (tree->right)
		heredoc_counter(setup, tree->right);
}

void	get_delimiter(t_setup *setup, t_redirections *red)
{
	if (setup->heredoc->delimiter)
		gc_free(g_gc, setup->heredoc->delimiter);
	setup->heredoc->delimiter = ft_strdup(red->file_name);
	red = red->next;
	return ;
}

void	heredoc_counter(t_setup *setup, t_tree *tree)
{
	t_redirections	*redir;

	redir = tree->redirections;
	if (!tree)
		return ;
	if (tree->cmd && tree->cmd->redirections)
	{
		while (redir)
		{
			if (redir->type == TOKEN_HERDOC)
				setup->heredoc_counter++;
			redir = redir->next;
		}
	}
	heredoc_counter_in_pipe(setup, tree);
}

void	close_fds(t_setup *setup)
{
	int	i;

	i = 0;
	if (setup->heredoc->fd[i])
	{
		while (setup->heredoc->fd[i])
		{
			close(setup->heredoc->fd[i]);
			i++;
		}
	}
}
