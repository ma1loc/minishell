#include "tokenizer.h"
#include "../srcs/mini_shell.h"

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

void copy_env_value_if_valid(t_expand_data *data, t_token *token)
{
  char *new;

  if (data->env_value)
  {
    new = data->env_value;
    if (token->quotes_info->quotes_type == 0 && check_space(new))
      new = skip_spaces_while_expand(token, new);
    strcpy(data->buff + data->buff_index, new);
    data->buff_index += strlen(new);
  }
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


