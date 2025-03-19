#include "tokenizer.h"
#include "../srcs/mini_shell.h"

void process_token_type_word(t_commande_state *state, t_token *current, t_args_list **list_args)
{
  if(state->current_cmd->name == NULL && current->value[0] != '\0')
        state->current_cmd->name = strdup(current->value);  // first word become the first command name
      else
        add_args_to_list(list_args, current);
}

void creat_node_pipe_commande(t_commande_state *state)
{
  state->new_cmd = malloc(sizeof(t_command));
  if(!state->new_cmd)
  {
    free(state->new_cmd);
    free(state);
    return;
  }
  state->new_cmd->name = strdup("|");
  state->new_cmd->args = NULL;
  state->new_cmd->redirections = NULL;
  state->new_cmd->type = TOKEN_PIPE;
  state->new_cmd->next = NULL;

   state->current_cmd->next = state->new_cmd;  // link the pip node
   state->current_cmd = state->new_cmd;
}

void creat_node_next_commande(t_commande_state *state)// creat new node for the next commande
{
  state->new_cmd = malloc(sizeof(t_command));
  if(!state->new_cmd)
  {
    free(state->new_cmd);
    free(state);
    return;
  }
  state->new_cmd->name = NULL;
  state->new_cmd->args = NULL;
  state->new_cmd->redirections = NULL;
  state->new_cmd->type = 0;
  state->new_cmd->next = NULL;

  state->current_cmd->next = state->new_cmd;
  state->current_cmd = state->new_cmd;
}


void process_token_type_pipe(t_commande_state *state, t_args_list **list_args)
{
   // current_cmd->type = current->type;
   if(list_args != NULL)
   {
     state->args_count = count_args_list(*list_args);
     state->current_cmd->args = malloc((state->args_count + 2) * sizeof(char *));
     fill_array(*list_args, state->current_cmd); // derefrence signle list arg to get the value

     state->current_cmd->args[state->args_count + 1] = NULL;
     // free_list_args(list_args);
     *list_args = NULL;  // rest the args list
   }
   else
   {
     state->current_cmd->args = malloc(sizeof(char *)); // if no args for this command
     state->current_cmd->args[0] = NULL;
   }
   creat_node_pipe_commande(state);  // creat node for pipe and link the pip node
   creat_node_next_commande(state); // creat new node for the next commande

}

void process_token_type_redir_in_her(t_commande_state *state, t_token *current)
{
  if(current->next && current->next->type == TOKEN_WORD) // next token shoud be the input filename
  {
    add_redirection_to_list(state->current_cmd, current->next->value, current->type);
    current = current->next; // skip filename token
  }
}

void process_token_type_redir_out_app(t_commande_state *state, t_token *current)
{
  if(current->next && current->next->type == TOKEN_WORD)
  {
    add_redirection_to_list(state->current_cmd, current->next->value, current->type);
    current = current->next;
  }
}

void process_args_last_cmd(t_commande_state *state, t_args_list *list_args)
{
  if(list_args != NULL)  // process argus for last command
  {
    state->args_count = count_args_list(list_args);
    state->current_cmd->args = malloc((state->args_count + 2) * sizeof(char *));
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
      if (state->current_cmd->name)  // Add this check
          state->current_cmd->args[0] = strdup(state->current_cmd->name);
      else
          state->current_cmd->args[0] = NULL;
      state->current_cmd->args[1] = NULL;
      // Don't call fill_array here since list_args is NULL
  }
}

t_command *creat_new_node_command(t_command *commandes)
{
  commandes = malloc(sizeof(t_command)); // creat new commande
  if(!commandes)
    return (NULL);
  commandes->name = NULL;
  commandes->args = NULL;
  commandes->redirections = NULL;
  commandes->type = 0;
  commandes->next = NULL;
  return(commandes);
}

void process_token(t_commande_state *state, t_token *current, t_args_list **list_args)
{
  if(current->type == TOKEN_WORD)  // if first token is word
  process_token_type_word(state, current, list_args);
else if(current->type == TOKEN_PIPE)
  process_token_type_pipe(state, list_args);
else if(current->type == TOKEN_RED_IN || current->type == TOKEN_HERDOC)
  process_token_type_redir_in_her(state, current);
else if(current->type == TOKEN_RED_OUT || current->type == TOKEN_APPEND)
  process_token_type_redir_out_app(state, current);
}

