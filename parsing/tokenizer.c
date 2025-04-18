#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../srcs/mini_shell.h"

t_quotes_info strip_quotes(char *str)
{
    t_quotes_info info;
    char *result;
    int len;
    int i;
    int j;

    info.quotes_type = 0;
    int in_dquote = 0;
    int in_squote = 0;

    len = strlen(str);
    result = malloc(len + 1);
    if (!result)
    {
      info.stripped_text = NULL;
      return info;
    }
    i = 0;  // index for original string
    j = 0;  // index for result string
    while (i < len)
    {
        if (str[i] == '"' && in_squote == 0)
        {
          if (in_dquote == 0)
          {
            in_dquote = 1;
            info.quotes_type = 2;
          }
          else
            in_dquote = 0;
        }
        else if (str[i] == '\'' && in_dquote == 0)
        {
          if (in_squote == 0)
          {
            in_squote = 1;
            info.quotes_type = 1;
          }
          else
            in_squote = 0;
        }
        else
          result[j++] = str[i];  // Copy non-quote characters
        i++;
    }
    result[j] = '\0';
    info.stripped_text = result;
    // if (j == 0 && len > 0)
    //     return info;
    if (j == 0 && len == 0)
    {
        free(result);
        info.stripped_text = NULL;
    }
    return info;
}


int check_syntax(char *input, int len, int *i)
{
//////////////////////////////////////  for pip in bigging or in midel or in the end
  int j;

  j = 0;
  if(input[*i] == '|')
  {
    if(*i == 0)
      return(1);
    if(*i > 0 && input[*i - 1] == '|')
      return(1);
  }
  if(input[len - 1] == '|')
    return(1);
//////////////////////////////////////  check if there is only spaces or tabs after redir 
  if(input[*i] == '<' || input[*i] == '>')
  {
    if(*i + 1 < len && input[*i] == input[*i + 1]) // check for << or >>
    {
      j = *i + 2;
      while(j < len && (input[j] == ' ' || input[j] == '\t'))
        j++;
      if(j >= len && input[j] == '\0')
        return(1);
    }
    else  // check for < or >
    {
      j = *i + 1;
      while(j < len && (input[j] == ' ' || input[j] == '\t'))
        j++;
      if(j >= len || input[j] == '\0')
        return(1);
    }
  }
  ////////////////////////////////////////////  original checks                  
  else if(input[len - 1] == '<' && input[len - 2] == '<')
    return(1);
  else if(input[0] == '<' && input[1] == '\0')
    return(1);
  else if(input[0] == '>' && input[1] == '>' && input[2] == '\0')
    return(1);
  else if (input[len - 1] == '>')
    return(1);
  else if(input[*i] == '>' && input[*i + 1] == '<')
    return(1);
  else if(input[0] == '<' && input[1] == '<' && input[2] == '<' && input[3] == '<')
    return(1);
  else if(input[0] == '>' && input[1] == '>' && input[3] == '>')
    return(1);
  else if(input[0] == '<' && input[1] == '<' && input[2] == '\0')
    return(1);
  return(0);
}
int check_quotes_syntax(t_setup *setup) // fuc to check if quoest match inclosed or no
{
  int i;
  int in_quoets;
  char quoest_char;
  int len;

  i = 0;
  in_quoets = 0;
  quoest_char = 0;
  len = strlen(setup->input);
  while(setup->input[i] != '\0')
  {
    if(setup->input[i] != '\0' && (setup->input[i] == ' ' || setup->input[i] == '\t'))
    {
      i++;
      continue;
    }
    if(check_syntax(setup->input, len, &i) != 0)
    {
      in_quoets = 1;
      break;
    }
    else if ((setup->input[i] == '"' || setup->input[i] == '\'') && (quoest_char == setup->input[i] || in_quoets == 0))
    {
      if(!in_quoets)
      {
        in_quoets = 1;
        quoest_char = setup->input[i];
      }
      else
      {
        in_quoets = 0;
        quoest_char = 0;
      }
    }
    i++;
  }
  if(in_quoets)
  {
    ft_perror(setup, "syntax error near unexpected token\n", SYNTAX_ERROR);
    return(1);
  }
  return(0);
}



t_token *add_token( t_token **head, char *value, t_token_type type, int quotes_type) // function creat new token and add it to the linked list
{
  t_token *new_token;
  t_token *current;

  new_token = malloc(sizeof(t_token));
  if(!new_token)
    return(NULL);
  new_token->value = strdup(value);  // copy the value
  new_token->type = type;
  new_token->next = NULL;

  new_token->quotes_info = malloc(sizeof(t_quotes_info));
  if(!new_token->quotes_info)
  {
    free(new_token->value);
    free(new_token);
    return(NULL);
  }
  new_token->quotes_info->quotes_type = quotes_type;
  if(*head == NULL)      // if list empty make this token the first in the list
  {
   *head = new_token;
   return(new_token);
  }

  current = *head;
  while(current->next != NULL)
  {
    current = current->next;
  }
  current->next = new_token;
  return(new_token);
}

t_token *add_token_at_position(t_token **head, char *value, t_token_type type, int quotes_type, t_token *position)
{
    t_token *new_token;
    
    new_token = malloc(sizeof(t_token));
    if(!new_token)
        return(NULL);
    new_token->value = strdup(value);  // copy the value
    new_token->type = type;
    new_token->is_split = 0; // Set is_split to 0 for new tokens
    
    new_token->quotes_info = malloc(sizeof(t_quotes_info));
    if(!new_token->quotes_info)
    {
        free(new_token->value);
        free(new_token);
        return(NULL);
    }
    new_token->quotes_info->quotes_type = quotes_type;
    
    if(*head == NULL || position == NULL)  // If list is empty or position is NULL, add at the beginning
    {
        new_token->next = *head;
        *head = new_token;
        return(new_token);
    }
    
    // Insert after the position token
    new_token->next = position->next;
    position->next = new_token;
    
    return(new_token);
}

// void handel_is_split(t_token *tokens, t_token **head)
// {
//   t_quotes_info info;
//   char *input = NULL;
//   t_token *current = NULL;
//   t_token *tmp = NULL;
//   int i;
//   int j;
//   char buff[1024];

//   i = 0;
//   j = 0;
//   current = tokens;

//   // setup->token = tokens;
//   input = current->value;

//   if(!input)
//     return;
//   while(current)
//   {
//     if(current->is_split == 1)
//     {
//       while(input[i] != '\0')
//       {
//         if(input[i] == ' ' || input[i] == '\t')
//         {
//           if(j > 0)
//           {
//             buff[j] = '\0';
//             info.stripped_text = buff; 
//             add_token_at_position(head, info.stripped_text, TOKEN_WORD, info.quotes_type, current);
//           }
//           j = 0;
//           i++;
//         }
//         else
//           buff[j++] = input[i++];
//       }
//       if(j > 0)
//       {
//         buff[j] = '\0';
//         info.stripped_text = buff; 
//         add_token_at_position(head, info.stripped_text, TOKEN_WORD, info.quotes_type, current);
//       }
//       j = 0;
//       i++;
//       tmp = current;
//       current = current->next;
//       remove_token(head,tmp);
//       continue;
//     }
//     // add_args_to_list(list_args, current);
//     current = current->next;
//   }
// }

void handel_is_split(t_token *tokens, t_token **head)
{
  t_quotes_info info;
  char *input = NULL;
  t_token *current = NULL;
  t_token *prev = NULL;
  t_token *last_inserted = NULL;
  int i;
  int j;
  char buff[1024];

  current = tokens;

  while(current)
  {
    if(current->is_split == 1)
    {
      input = current->value;
      if(!input)
      {
        current = current->next;
        continue;
      }

      // Store previous node to use for insertion point
      if(prev == NULL)
        last_inserted = NULL; // We'll insert at the head
      else
        last_inserted = prev;

      // Reset counters for this token
      i = 0;
      j = 0;
      
      // Get quotes_type from current token
      info.quotes_type = current->quotes_info ? current->quotes_info->quotes_type : 0;

      while(input[i] != '\0')
      {
        if(input[i] == ' ' || input[i] == '\t')
        {
          if(j > 0)
          {
            buff[j] = '\0';
            
            // Insert after the last inserted token
            last_inserted = add_token_at_position(head, buff, TOKEN_WORD, info.quotes_type, last_inserted);
            j = 0;
          }
          i++;
        }
        else
          buff[j++] = input[i++];
      }
      
      if(j > 0)
      {
        buff[j] = '\0';
        
        // Insert after the last inserted token
        last_inserted = add_token_at_position(head, buff, TOKEN_WORD, info.quotes_type, last_inserted);
      }
      
      // Store next before removing current
      t_token *next = current->next;
      
      // Remove the original token
      remove_token(head, current);
      
      // Move to next token
      current = next;
    }
    else
    {
      prev = current;
      current = current->next;
    }
  }
}

t_token *tokenize(t_setup *setup)
{
  t_tokinizer_state *state;
  t_token *tokens;
  char *input;

  input = setup->input;
  tokens = NULL;
  state = malloc(sizeof(t_tokinizer_state));
  if(!state)
    return NULL;
  state->i = 0;
  state->j = 0;
  memset(state->buff, 0, sizeof(state->buff));
  if(!setup->input || check_quotes_syntax(setup) != 0)
    return (free(state), NULL);
  while(input[state->i] != '\0')
  {
    if(input[state->i] == ' ' || input[state->i] == '\t')    // skip spaces or tabsbetween tokens
      process_spaces(state, &tokens);
    else if(input[state->i] == '|' || input[state->i] == '<' || input[state->i] == '>')  // Handle special tokens (pipe, redirections)
      process_special_tokens(input, state, &tokens);
    else if(input[state->i] == '$')
      process_dollar(input, state, &tokens);
    else if(input[state->i] == '"' || input[state->i] == '\'') // Handle quoted sections within a word
      process_quotes(input, state, setup, &tokens);
    else
      process_normal_word(input,state);  // just a regular character in a word
  }
  process_remainder_text(state, &tokens);  // don't forget any remaining text in the buffer
  expand_env_vars(tokens, setup); // expand them before return to return expanded tokens
  handel_is_split(tokens,&tokens);
  return (free(state), tokens);
}

// void print_tokens( t_token *tokens) //////////////// print tokens
// {
//   while(tokens != NULL)
//   {
//     printf("token => [%s], type => [%d], quotes_type => [%d], is_space => [%d] , is_split => [%d]\n", tokens->value, tokens->type, tokens->quotes_info->quotes_type, tokens->is_space, tokens->is_split);
//     tokens = tokens->next;
//   }
// }


// void free_tokens(t_token *tokens)
// {
//   t_token *current;
//   t_token *next;

//   current = tokens;
//   while(current)
//   {
//     next = current->next;
//     free(current->value);  // free string
//     free(current);         // free token struct
//     current = next;
//   }
// }


// t_command *find_pipe_node(t_command *commands) //////////////////////////////////  check pipe node
// {
//     t_command *current = commands;
//     while (current)
//     {
//         if (current->type == TOKEN_PIPE)
//             return current; // Return the pipe node
//         current = current->next;
//     }
//     return NULL; // No pipe found
// }




// int main() /////////////////////////////////////////////////
// {
//     // char *input = "echo        \"hello \'\'      \" \"world\"";
//     // char *input ="ls -la | cat | << wc -l";
//     // char *input = "<< ls cat echo walo";
//     // char *input = " ls | cat | hello ";
//     char *input = "echo $PATH";



//     printf("Raw input: %s\n", input);
//     // t_env env1 = {"PATH", "/usr/bin:/bin:/usr/sbin:/sbin", NULL};
//     t_setup *setup;
//     // setup->env = &env1;
//     // Tokenize the input
//     // t_setup *setup;
//     t_token *tokens = tokenize(input, setup);
//     tokens = expand_env_vars(tokens, setup);
//     // Print the tokens
//     printf("Tokens:\n");
//     print_tokens(tokens);
//     // free_tokens(tokens);

//     // Parse the tokens
//     t_command *commands = pars_tokens(tokens);
//     t_command *pipe_node = find_pipe_node(commands);

//     // Print the parsed commands
//     printf("\nParsed Commands:\n");
//     print_commands(commands);
//     //

//     if (pipe_node)
//     printf("Found a pipe node in the command list!\n");
//     else
//     printf("No pipe node found in the command list.\n");


//     return 0;
// }
