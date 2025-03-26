#include "tokenizer.h"
#include "../srcs/mini_shell.h"

char *get_env_value(char *name, t_setup *setup)
{
  t_env *env;
  char *striped_name;

  if(!name || !setup || !setup->env)
    return(NULL);
  env = setup->env;
  if(name[0] == '$')
    striped_name = name + 1;
  else
    return(NULL);

  while(env)
  {
    if(strcmp(env->key, striped_name) == 0)
      return(env->value);
    env = env->next;
  }
  return(NULL);
}

t_token *expand_env_vars(t_token *tokens, t_setup *setup)
{
  t_token *current;
  char *env_value;

  current = tokens;
  while(current)
  {
    env_value = get_env_value(current->value, setup);
    if(env_value != NULL)
    {
      free(current->value);
      current->value = strdup(env_value);
    }
    current = current->next;
  }
  return(tokens);
}