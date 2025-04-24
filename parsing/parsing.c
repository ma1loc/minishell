# include "mini_shell.h"

void	process_token(t_commande_state *state, t_token *current, t_args_list **list_args)
{
	int		found_cmd_name;
	t_token	*head;

	found_cmd_name = 0;
	head = current;
	while (current != NULL)
	{
    if(check_current_type(current->type))
		    current = process_token_type_redir(state, current);
		else if (current && current->type == TOKEN_WORD)
		{
			if (join_tokens(&current, head))
				continue ;
			set_command_name(state, current, &found_cmd_name);
			add_args_to_list(list_args, current);
		}
		else if (current && current->type == TOKEN_PIPE)
		{
			process_token_type_pipe(state, list_args);
			found_cmd_name = 0;
		}
		if (current)
			current = current->next;
		process_args_last_cmd(state, *list_args);
	}
}

t_command *pars_tokens(t_setup *setup)
{
  t_command *commandes;
  t_token *current;
  t_args_list *list_args;
  current = setup->token;
  if(setup->token == NULL)
    return NULL;
  commandes = NULL;
  list_args = NULL;
  t_commande_state *state;    // state to use current commande and new onece
  state = gc_malloc(g_gc, sizeof(t_commande_state));
  if(!state)
    return(NULL);
  ft_memset(state, 0 , sizeof(t_commande_state));
  commandes = creat_new_node_command(commandes);  // create first command node
  state->current_cmd = commandes;   // track current commande
  current = setup->token; // linked list of tokens
  process_token(state, current, &list_args);
  gc_free(g_gc, state);
  return(commandes);
}

t_args_list *add_args_to_list(t_args_list **list_head, t_token *token)
{
  t_args_list *current_arg;
  t_args_list *new_arg;

  if(!token || !token->value)
    return(NULL);
  new_arg = gc_malloc(g_gc, sizeof(t_args_list));
  if(!new_arg)
    return (NULL);
  new_arg->value = ft_strdup(token->value);
  new_arg->type = token->type;
  new_arg->next = NULL;
  if(*list_head == NULL)
  {
    *list_head = new_arg;
    return(new_arg);
  }
  current_arg = *list_head;
  while(current_arg->next != NULL)
  {
    current_arg = current_arg->next;
  }
  current_arg->next = new_arg;
  return(new_arg);
}

int count_args_list(t_args_list *args)
{
  t_args_list *tmp;
  int i;

  tmp = args;
  i = 0;
  while(tmp != NULL)
  {
    i++;
    tmp = tmp->next;
  }
  return(i);
}

void fill_array(t_args_list *list, t_command *cmd)
{
    t_args_list *current;
    int i;

    i = 0;
    current = list;

    if (!current || !cmd || !cmd->name)
        return;

    cmd->args[i++] = ft_strdup(cmd->name);

    if (current != NULL && ft_strcmp(current->value, cmd->name) == 0)
        current = current->next;

    process_args(current, cmd, &i);
}
