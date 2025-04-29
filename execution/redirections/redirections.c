/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:01:48 by yanflous          #+#    #+#             */
/*   Updated: 2025/04/22 20:01:50 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	restored_org_red(int std_in, int std_out)
{
	dup2(std_in, STDIN_FILENO);
	dup2(std_out, STDOUT_FILENO);
	close(std_in);
	close(std_out);
}

int	get_red(t_setup *setup, t_tree *tree, t_redirections *redir)
{
	int	status;

	status = 0;
	if (redir->type == TOKEN_RED_IN)
		status = red_input(setup, tree, redir);
	else if (redir->type == TOKEN_RED_OUT)
		status = red_output(setup, tree, redir);
	else if (redir->type == TOKEN_APPEND)
		status = red_append(setup, tree, redir);
	else if (redir->type == TOKEN_HERDOC)
		status = red_heredoc(setup, tree, redir);
	return (status);
}

void	execute_redirections(t_tree *tree, t_setup *setup)
{
	int				status;
	int				save_stdin;
	int				save_stdout;
	t_redirections	*red;

	status = 0;
	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	red = tree->cmd->redirections;
	while (red != NULL)
	{
		status = get_red(setup, tree, red);
		if (status == -1)
			break ;
		red = red->next;
	}
	if (status == -1)
		return (restored_org_red(save_stdin, save_stdout), (void)0);
	if (status == 0)
		execute_commands(tree, setup);
	restored_org_red(save_stdin, save_stdout);
}
