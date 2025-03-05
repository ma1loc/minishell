#include "../../srcs/mini_shell.h"

// >>> geting the value of a key in the env (i thing we don't not need it?)
char	*get_env(t_env *env_list, char *key)
{
	while (env_list)
	{
		if (ft_strncmp(env_list->key, key, ft_strlen(key)) == 0)
			return(env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

// >>> set the new key and value of change key value in the env.
void	set_env(t_env **env_list, char *key, char *value)
{
	t_env	*current;
	t_env	*last_node;

	current = *env_list;
	last_node = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (free(current->value), \
			current->value = ft_strdup(value), (void)0);
		current = current->next;
	}
	current = *env_list;
	last_node = ft_lstlast(current);
	last_node->next = malloc(sizeof(t_env));
	if (!last_node)
		return ;
	last_node->key = ft_strdup(key);
	last_node->value = ft_strdup(value);
	last_node->next = NULL;
}