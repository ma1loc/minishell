#include "mini_shell.h"

// >>> geting the value of a key in the env (i thing we don't not need it?)
// char	*get_env(t_env *env_list, char *key)
// {
// 	while (env_list)
// 	{
// 		if (ft_strncmp(env_list->key, key, ft_strlen(key)) == 0)
// 			return(env_list->value);
// 		env_list = env_list->next;
// 	}
// 	return (NULL);
// }

// >>> set the new key and value of change key value in the env.
// void	set_env(t_env **env_list, char *key, char *value)
// {
// 	t_env	*current;
// 	t_env	*last_node;

// 	current = *env_list;
// 	last_node = NULL;
// 	while (current)
// 	{
// 		if (ft_strcmp(current->key, key) == 0)
// 			return (free(current->value),
// 			current->value = ft_strdup(value), (void)0);
// 		current = current->next;
// 	}
// 	current = *env_list;
// 	last_node = ft_lstlast(current);
// 	last_node->next = malloc(sizeof(t_env));
// 	if (!last_node)
// 		return ;
// 	last_node->key = ft_strdup(key);
// 	last_node->value = ft_strdup(value);
// 	last_node->next = NULL;
// }

void	set_env(t_env **env_list, char *key, char *value)
{
	t_env	*current;
	t_env	*last_node;
	t_env	*new_node;

	if (!env_list)
		return ;
	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	if (!*env_list)
	{
		*env_list = malloc(sizeof(t_env));
		if (!*env_list)
			return ;
		(*env_list)->key = ft_strdup(key);
		(*env_list)->value = ft_strdup(value);
		(*env_list)->next = NULL;
		return ;
	}
	last_node = ft_lstlast(*env_list);
	if (!last_node)
		return ;
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	last_node->next = new_node;
}
