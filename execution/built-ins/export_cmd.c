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
			if (value == NULL)
				return ;
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

// void	export_cmd(t_setup	*built_in)
// {
// 	if (!built_in->cmd->args[1])
// 		env_cmd(built_in);
	
// }

// >>> Key must start with letter or underscore
// >>> bash: export: `5': not a valid identifier
// >>> bash: export: `h-ello': not a valid identifier

void	export_cmd(t_setup	*built_in)
{
	char	**args;
	int		i;
	char	**dividing_args;

	i = 1;
	args = built_in->cmd->args;
	dividing_args = NULL;
	if (!args[i])
		env_cmd(built_in);
	// >>> here i have to split = in the args and set them ot the env
	else if (args[i])
	{
		// printf("arg -> %s\n", args[i]);
		while (args[i])
		{
			if (ft_strchr(args[i], '='))
			{	// update the export variable to fix litter on
				dividing_args = ft_split(args[i], '=');
				set_env(&built_in->env_list, dividing_args[0], dividing_args[1]);
				free_spliting(dividing_args);
			}
			else
				set_env(&built_in->env_list, args[i], NULL);
			i++;
		}
	}
}