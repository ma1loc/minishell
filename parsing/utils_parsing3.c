/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytabia <ytabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:09:48 by ytabia            #+#    #+#             */
/*   Updated: 2025/04/24 20:06:41 by ytabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	creat_node_pipe_commande(t_commande_state *state)
{
	state->new_cmd = gc_malloc(g_gc, sizeof(t_command));
	if (!state->new_cmd)
	{
		gc_free(g_gc, state->new_cmd);
		gc_free(g_gc, state);
		return ;
	}
	state->new_cmd->name = ft_strdup("|");
	state->new_cmd->args = NULL;
	state->new_cmd->redirections = NULL;
	state->new_cmd->type = TOKEN_PIPE;
	state->new_cmd->next = NULL;
	state->current_cmd->next = state->new_cmd;
	state->current_cmd = state->new_cmd;
}

void	creat_node_next_commande(t_commande_state *state)
{
	state->new_cmd = gc_malloc(g_gc, sizeof(t_command));
	if (!state->new_cmd)
	{
		gc_free(g_gc, state->new_cmd);
		gc_free(g_gc, state);
		return ;
	}
	state->new_cmd->name = NULL;
	state->new_cmd->args = NULL;
	state->new_cmd->redirections = NULL;
	state->new_cmd->type = 0;
	state->new_cmd->next = NULL;
	state->current_cmd->next = state->new_cmd;
	state->current_cmd = state->new_cmd;
}

void	process_token_type_pipe(t_commande_state *state,
		t_args_list **list_args)
{
	if (list_args != NULL)
	{
		state->args_count = count_args_list(*list_args);
		state->current_cmd->args = gc_malloc(g_gc, (state->args_count + 2)
				* sizeof(char *));
		fill_array(*list_args, state->current_cmd);
		state->current_cmd->args[state->args_count + 1] = NULL;
		*list_args = NULL;
	}
	else
	{
		state->current_cmd->args = gc_malloc(g_gc, sizeof(char *));
		state->current_cmd->args[0] = NULL;
	}
	creat_node_pipe_commande(state);
	creat_node_next_commande(state);
}

t_token	*process_token_type_redir(t_commande_state *state, t_token *current)
{
	if (current->next && current->next->type == TOKEN_WORD)
	{
		add_redirection_to_list(state->current_cmd, current->next->value,
			current->type);
		return (current->next);
	}
	return (current);
}

void	process_args_last_cmd(t_commande_state *state, t_args_list *list_args)
{
	if (list_args != NULL)
	{
		state->args_count = count_args_list(list_args);
		state->current_cmd->args = gc_malloc(g_gc, (state->args_count + 2)
				* sizeof(char *));
		if (!state->current_cmd->args)
			return ;
		fill_array(list_args, state->current_cmd);
		state->current_cmd->args[state->args_count + 1] = NULL;
		list_args = NULL;
	}
	else if (state->current_cmd->args == NULL)
	{
		state->current_cmd->args = gc_malloc(g_gc, 2 * sizeof(char *));
		if (!state->current_cmd->args)
			return ;
		if (state->current_cmd->name)
			state->current_cmd->args[0] = ft_strdup(state->current_cmd->name);
		else
			state->current_cmd->args[0] = NULL;
		state->current_cmd->args[1] = NULL;
	}
}
