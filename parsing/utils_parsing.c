#include "tokenizer.h"
#include "../srcs/mini_shell.h"

// void process_token_type_word(t_commande_state *state, t_token *current, t_args_list **list_args)
// {
//   if(state->current_cmd->name == NULL && current->value[0] != '\0')
//         state->current_cmd->name = strdup(current->value);  // first word become the first command name
//       else
//         add_args_to_list(list_args, current);
// }

static int	count_numbers(int n)
{
	int				count;
	unsigned int	num;

	num = n;
	count = 0;
	if (n < 0)
	{
		num = -n;
		count++;
	}
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num = num / 10;
		count++;
	}
	return (count);
}

static char	*fill_ptr(int num, char *ptr)
{
	if (num == 0)
	{
		ptr[0] = '0';
		ptr[1] = '\0';
	}
	return (ptr);
}

char	*ft_itoa_(int n)
{
	size_t			num_len;
	unsigned int	num;
	char			*ptr;

	num_len = count_numbers(n);
	ptr = malloc(sizeof(char) * (num_len + 1));
	if (!ptr)
		return (NULL);
	if (n < 0)
	{
		num = -n;
		ptr[0] = '-';
	}
	else
		num = n;
	fill_ptr(num, ptr);
	if (num > 0)
		ptr[num_len] = '\0';
	while (num > 0)
	{
		ptr[--num_len] = (num % 10) + '0';
		num = num / 10;
	}
	return (ptr);
}
static void	cpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

char	*ft_strjoin_(char *s1, char *s2)
{
	size_t	total_len;
	char	*ptr;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (NULL);
	if (!s2)
		return (strdup(s1));
	total_len = ft_strlen(s1) + ft_strlen(s2);
	ptr = malloc(sizeof(char) * (total_len + 1));
	if (!ptr)
		return (NULL);
	cpy(ptr, s1);
	cpy(ptr + ft_strlen(s1), s2);
	return (ptr);
}
///////////////////////////////////////////////////
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
   if(list_args != NULL)  // if there is args for current cmd
   {
     state->args_count = count_args_list(*list_args);
     state->current_cmd->args = malloc((state->args_count + 2) * sizeof(char *));
     fill_array(*list_args, state->current_cmd); // derefrence signle pointer list args to get the value to fill args

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

t_token *process_token_type_redir(t_commande_state *state, t_token *current)
{
  if(current->next && current->next->type == TOKEN_WORD) // next token shoud be the input filename or delimiter
  {
    add_redirection_to_list(state->current_cmd, current->next->value, current->type);
    return(current->next); // skip filename  or delemiter token
  }
  return(current);
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
void	remove_token(t_token **head, t_token *current)
{
	t_token	*temp;
	t_token	*prev;

	if (head == NULL || *head == NULL || current == NULL)
		return ;
	if (*head == current)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp->value);
		if (temp->quotes_info)
			free(temp->quotes_info);
		free(temp);
		return ;
	}
	prev = *head;
	while (prev && prev->next != current)
		prev = prev->next;
	if (prev)
	{
		prev->next = current->next;
		free(current->value);
		free(current);
	}
}
void process_token(t_commande_state *state, t_token *current, t_args_list **list_args)
{
  int found_cmd_name = 0;
  t_token *head = current;
  while (current != NULL) // process each token
  {
    if (current->type == TOKEN_RED_IN || current->type == TOKEN_HERDOC || current->type == TOKEN_RED_OUT || current->type == TOKEN_APPEND || current->type == TOKEN_RED_INOUT)
    {
      // process redirection first
      current = process_token_type_redir(state, current);
    }
    else if (current->type == TOKEN_WORD)
    {
        if(current->is_space == -1 && current->next)  // if no space between token 
        {
          current->value = ft_strjoin_(current->value, current->next->value); // add ft later
          current->is_space = current->next->is_space;
          remove_token(&head,current->next);
          continue;
        }
        if (!found_cmd_name)
        {   // if found cmd name become 1 so skeep to add name
            // first word token not part of a redirection becomes command name
            state->current_cmd->name = strdup(current->value);
            found_cmd_name = 1;
        }
        add_args_to_list(list_args, current);
    }
    else if (current->type == TOKEN_PIPE)
    {
      process_token_type_pipe(state, list_args);
      found_cmd_name = 0; // reset for next command
    }
    current = current->next;
    process_args_last_cmd(state, *list_args); // process any remaining arguments
  }
}
