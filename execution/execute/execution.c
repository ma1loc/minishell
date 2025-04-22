/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:41:00 by yanflous          #+#    #+#             */
/*   Updated: 2025/04/22 11:41:03 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	execute_externals(t_setup *setup)
{
	pid_t	pid;
	int		status;

	pid = 0;
	setup->cmd_path = path_resolver(setup);
	if (!setup->cmd_path)
		return (ft_perror(setup, "command"\
		" not found\n", CMD_NOT_FOUND), (void)0);
	pid = set_fork(setup);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (execve(setup->cmd_path, setup->cmd->args, setup->exec_env) == -1)
			ft_perror(setup, NULL, EXIT_FAILURE);
		return (gc_destroy(g_gc), exit(EXIT_FAILURE), (void)0);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, main_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal_status(setup, status);
}

void	execute_commands(t_tree *tree, t_setup *setup)
{
	if (!tree)
		return ;
	if (is_built_in(tree->name))
	{
		execute_internals(tree->cmd, setup);
		return ;
	}
	execute_externals(setup);
}

void	execution(t_tree *tree, t_setup *setup)
{
	if (tree->type == TOKEN_WORD)
	{
		if (tree->cmd->redirections == NULL)
		{
			setup->fork_flag = 1;
			execute_commands(tree, setup);
		}
		else
		{
			setup->fork_flag = 1;
			execute_redirections(tree, setup);
		}
	}
	else if (tree->type == TOKEN_PIPE)
	{
		setup->fork_flag = 0;
		execute_pipes(tree, setup);
	}
	if (setup->heredoc_flag)
		cleanup_heredoc(setup);
	setup->exec_env = update_exec_envp(setup);
	setup->fork_flag = 0;
}
