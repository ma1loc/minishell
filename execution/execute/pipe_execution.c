/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:43:49 by yanflous          #+#    #+#             */
/*   Updated: 2025/04/22 11:43:51 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	first_child_process(t_setup *setup, t_tree *tree, int *fd)
{
	int	exit_stat;

	exit_stat = 0;
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		ft_perror(setup, NULL, EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}
	close(fd[1]);
	if (tree->left)
	{
		if (tree->left->type == TOKEN_WORD)
		{
			setup->cmd = tree->left->cmd;
			if (tree->left->cmd && tree->left->cmd->redirections)
				execute_redirections(tree->left, setup);
			else
				execute_commands(tree->left, setup);
		}
		else
			execution(tree->left, setup);
	}
	exit_stat = setup->exit_stat;
	return (gc_destroy(g_gc), exit(exit_stat), (void)0);
}

void	second_child_process(t_setup *setup, t_tree *tree, int *fd)
{
	int	exit_stat;

	exit_stat = 0;
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		ft_perror(setup, NULL, EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
	if (tree->right)
	{
		if (tree->right->type == TOKEN_WORD)
		{
			setup->cmd = tree->right->cmd;
			if (tree->right->cmd && tree->right->cmd->redirections)
				execute_redirections(tree->right, setup);
			else
				execute_commands(tree->right, setup);
		}
		else
			execution(tree->right, setup);
	}
	exit_stat = setup->exit_stat;
	return (gc_destroy(g_gc), exit(exit_stat), (void)0);
}

void	execute_pipes(t_tree *tree, t_setup *setup)
{
	int		fd[2];
	pid_t	pid_1;
	pid_t	pid_2;
	int		status1;
	int		status2;

	set_pipe(setup, fd);
	pid_1 = set_first_fork(setup, fd);
	if (pid_1 == 0)
		first_child_process(setup, tree, fd);
	pid_2 = set_second_fork(setup, pid_1, fd);
	if (pid_2 == 0)
		second_child_process(setup, tree, fd);
	close(fd[0]);
	close(fd[1]);
	if (pid_1 < 0 || pid_2 < 0)
		return (gc_destroy(g_gc), exit(EXIT_FAILURE), (void)0);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid_1, &status1, 0);
	waitpid(pid_2, &status2, 0);
	signal_status(setup, status2);
	signal(SIGINT, main_sigint);
	signal(SIGQUIT, SIG_IGN);
}
