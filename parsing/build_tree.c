/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytabia <ytabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:09:18 by ytabia            #+#    #+#             */
/*   Updated: 2025/04/20 16:09:19 by ytabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "../srcs/mini_shell.h"

t_tree	*create_leaf_node(t_command *cmd)
{
	t_tree	*leaf;

	leaf = malloc(sizeof(t_tree));
	if (!leaf)
		return (NULL);
	if (cmd->name != NULL)
		leaf->name = strdup(cmd->name);
	else
		leaf->name = NULL;
	leaf->type = TOKEN_WORD;
	leaf->args = cmd->args;
	leaf->cmd = cmd;
	leaf->redirections = cmd->redirections;
	leaf->left = NULL;
	leaf->right = NULL;
	return (leaf);
}

t_tree	*create_pipe_node(t_command *pip_cmd)
{
	t_tree	*root;

	root = malloc(sizeof(t_tree));
	if (!root)
		return (NULL);
	root->name = NULL;
	root->args = NULL;
	root->redirections = NULL;
	root->type = TOKEN_PIPE;
	root->cmd = pip_cmd;
	root->left = NULL;
	root->right = NULL;
	return (root);
}

t_command	*find_pipe_command(t_command *commandes, t_command **prev_cmd)
{
	t_command	*pip_cmd;

	pip_cmd = commandes;
	*prev_cmd = NULL;
	while (pip_cmd != NULL && pip_cmd->type != TOKEN_PIPE)
	{
		*prev_cmd = pip_cmd;
		pip_cmd = pip_cmd->next;
	}
	return (pip_cmd);
}

t_tree	*build_tree_commande(t_command *commandes)
{
	t_command	*pip_cmd;
	t_command	*prev_cmd;
	t_tree		*root;
	t_command	*right_cmds;

	if (!commandes)
		return (NULL);
	pip_cmd = find_pipe_command(commandes, &prev_cmd);
	if (pip_cmd == NULL)
		return (create_leaf_node(commandes));
	right_cmds = pip_cmd->next;
	root = create_pipe_node(pip_cmd);
	if (!root)
		return (NULL);
	if (prev_cmd != NULL)
	{
		prev_cmd->next = NULL;
		root->left = (build_tree_commande(commandes));
	}
	if (right_cmds != NULL)
		root->right = (build_tree_commande(right_cmds));
	return (root);
}
