#include "tokenizer.h"
#include "../srcs/mini_shell.h"

// if(*ptr == '$' && !ft_isalpha(*ptr + 1) && *(ptr + 1) != '_')
//       {
//         expand_env_in_string(ptr, setup);
//         while(*ptr != '$' && *ptr != '\0')
//         {
//           buff[buff_index++] = *ptr;
//           ptr++;
//           break;
//         }
//       }

//>>> tests
// echo $HOME$ HOMEASDF >>> not valid //
// echo $HOME$*ASDF >>> not valid ..
// echo {$HOME}$  >>> not valid //
// echo "$PATH" '#PATH' $PATH >>> valid
// echo "$PATH"'#PATH'$PATH   >>> not valid
// minishell$


char *get_env_value(char *name, t_setup *setup)
{
  t_env *env;

  if(!name || !setup || !setup->env)
    return(NULL);
  env = setup->env;

  while(env)
  {
    if(strcmp(env->key, name) == 0)
      return(env->value);
    env = env->next;
  }
  return(NULL);
}
// int check_num_dolar(char *str)
// {
//   int i;
//   int count;
//   i = 0;
//   count = 0;
//   while(str[i] != '\0')
//   {
//     if(str[i] == '$' && str[i + 1] == '$')
//     {
//       count++;
//       i++;
//     }
//     i++;
//   }
//   if(count % 2 == 1)
//     return(1); // mean is odd 
//   return(0); // even
// }
char *expand_env_in_string(char *str, t_setup *setup)
{
  // t_expand *expand;
  int var_index;
  int buff_index = 0;
  char *env_value;
  char *rslt;
  char *ptr;
  char *var_start;
  char var_name[256];
  char buff[1024];
  t_token *token;

  token = setup->token;
  if(!str)
    return(NULL);
  if (!setup->token || !setup->token->quotes_info)
  {
    return(NULL);
  }
  // if(setup->token->quotes_info->quotes_type == 1)
  //   return(NULL);
    
  ptr = str;
  // printf("-> %s\n", token->value);
  while(*ptr)
  {
    if(*ptr == '$' && (token->quotes_info->quotes_type == 0 || token->quotes_info->quotes_type == 2))
    {
      if (*(ptr + 1) == '?') // expand exit stat
      {
        char *exit = ft_itoa_(setup->exit_stat); // add ft later
        strcpy(buff + buff_index, exit);
        buff_index += strlen(exit);
        ptr += 2;
        free(exit);
        continue;
      }
      if(*(ptr + 1) == '\0')
      {
        buff[buff_index++] = *ptr;
        break;
      }
      // reset variable collection
      ptr++;
      var_index = 0;
      var_start = ptr;  // save start var
      while(*var_start != '\0' && *var_start != '$' && (isalnum(*var_start) || *var_start == '_'))
      {
        var_name[var_index++] = *var_start++;
      }
      var_name[var_index] = '\0'; 
      env_value = get_env_value(var_name, setup);
      if(env_value != NULL)
      {
          strcpy(buff + buff_index, env_value);
          buff_index += strlen(env_value);
        }
      ptr = var_start; // skip to the end of variable name
      continue;     // skip the ptr++ at end of loop
    }
    else
      buff[buff_index++] = *ptr;
    ptr++;
  }
  buff[buff_index] = '\0';
  rslt = strdup(buff);
  return(rslt);
}

t_token *expand_env_vars(t_token *tokens, t_setup *setup)
{
  t_token *current;
  char *expanded;

  current = tokens;
  setup->token = current;
  while(current)
  {
    expanded = expand_env_in_string(current->value, setup);
    if(expanded != NULL)
    {
        free(current->value);
        current->value = expanded;
    }
    current = current->next;
    setup->token = current;
    }
    return(tokens);
  }


// t_token *expand_env_vars(t_token *tokens, t_setup *setup)
// {
//   t_token *current;
//   t_token *prev;
//   t_token *next;
//   char *expanded;
//   int is_first_token = 1;  // Flag to check if we're processing the first token
  
//   current = tokens;
//   prev = NULL;
  
//   while(current)
//   {
//     next = current->next;
    
//     if(current->value[0] == '$')
//     {
//       expanded = expand_env_in_string(current->value, setup);
      
//       if(expanded != NULL)
//       {
//         free(current->value);
//         current->value = expanded;
//       }
//       else // Variable not found
//       {
//         if(is_first_token)
//         {
//           // If the first token (command) is an undefined variable, 
//           // return NULL for the whole token list
//           // free_token_list(tokens);  ----------->// You need to implement this function
//           return NULL;
//         }
//         else
//         {
//           // Remove this token from the list (for arguments)
//           if(prev == NULL)
//             tokens = next;
//           else
//             prev->next = next;
          
//           free(current->value);
//           free(current);
          
//           current = next;
//           continue;
//         }
//       }
//     }
    
//     is_first_token = 0;  // After processing the first token, set flag to 0
//     prev = current;
//     current = next;
//   }
  
//   return tokens;
// }