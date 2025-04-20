#include "../srcs/mini_shell.h"
#include "tokenizer.h"

void	creat_node_pipe_commande(t_commande_state *state)
{
	state->new_cmd = malloc(sizeof(t_command));
	if (!state->new_cmd)
	{
		free(state->new_cmd);
		free(state);
		return ;
	}
	state->new_cmd->name = strdup("|");
	state->new_cmd->args = NULL;
	state->new_cmd->redirections = NULL;
	state->new_cmd->type = TOKEN_PIPE;
	state->new_cmd->next = NULL;
	state->current_cmd->next = state->new_cmd; // link the pip node
	state->current_cmd = state->new_cmd;
}

void	creat_node_next_commande(t_commande_state *state)
{
	state->new_cmd = malloc(sizeof(t_command));
	if (!state->new_cmd)
	{
		free(state->new_cmd);
		free(state);
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
if (list_args != NULL) // if there is args for current cmd
{
    state->args_count = count_args_list(*list_args);
    state->current_cmd->args = malloc((state->args_count + 2)
            * sizeof(char *));
    fill_array(*list_args, state->current_cmd);
        // derefrence signle pointer list args to get the value to fill args
    state->current_cmd->args[state->args_count + 1] = NULL;
    // free_list_args(list_args);
    *list_args = NULL; // rest the args list
}
else
{
    state->current_cmd->args = malloc(sizeof(char *));
        // if no args for this command
    state->current_cmd->args[0] = NULL;
}
creat_node_pipe_commande(state);
    // creat node for pipe and link the pip node
creat_node_next_commande(state); // creat new node for the next commande
}

t_token	*process_token_type_redir(t_commande_state *state, t_token *current)
{
	if (current->next && current->next->type == TOKEN_WORD)
		// next token shoud be the input filename or delimiter
	{
		add_redirection_to_list(state->current_cmd, current->next->value,
			current->type);
		return (current->next); // skip filename  or delemiter token
	}
	return (current);
}

void	process_args_last_cmd(t_commande_state *state, t_args_list *list_args)
{
	if (list_args != NULL) // process argus for last command
	{
		state->args_count = count_args_list(list_args);
		state->current_cmd->args = malloc((state->args_count + 2)
				* sizeof(char *));
		if (!state->current_cmd->args)
			return ;
		fill_array(list_args, state->current_cmd);
		state->current_cmd->args[state->args_count + 1] = NULL;
		// free_list_args(list_args);
		list_args = NULL;
	}
	else if (state->current_cmd->args == NULL)
	{
		state->current_cmd->args = malloc(2 * sizeof(char *));
		if (!state->current_cmd->args)
			return ;
		if (state->current_cmd->name) // add this check
			state->current_cmd->args[0] = strdup(state->current_cmd->name);
		else
			state->current_cmd->args[0] = NULL;
		state->current_cmd->args[1] = NULL;
	}
}



