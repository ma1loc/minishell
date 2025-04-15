#include "tokenizer.h"
#include "../srcs/mini_shell.h"

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

char *skip_spaces_while_expand(t_token *token,char *str)
{
  int i;
  int j;
  char *new_one;
  
  i = 0;
  j = 0;
  if (!str)
    return NULL;
  new_one = malloc(ft_strlen(str) + 1);
  while (str[i])
  {
    if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
    {
      new_one[j++] = ' '; 
      i++;
    }
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
      i++;
    new_one[j++] = str[i++];
    token->is_split = 1;
  }
  new_one[j] = '\0';
  return new_one;
}

char *expand_env_in_string(char *str, t_setup *setup)
{
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
    
  ptr = str;
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
          char *new = env_value;
          if(token->quotes_info->quotes_type == 0 && check_space(new))
            new = skip_spaces_while_expand(token,new);
          strcpy(buff + buff_index, new);
          buff_index += strlen(new);
          //token->is_split = 1;
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

int check_space(char *str)
{
  int i;

  i = 0;
  while(str[i])
  {
    if(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
      return(1);
    i++;
  }
  return(0);
}

void expand_env_vars(t_token *tokens, t_setup *setup)
{
  t_token *current;
  char *expanded;
  // t_args_list *list_args = NULL;

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
}
