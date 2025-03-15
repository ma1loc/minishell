#include "mini_shell.h"

// >>> geting the value of a key in the env (i thing we don't not need it?)
void	set_env(t_env **env, char *key, char *value)
{
	t_env	*current;
	t_env	*last_node;
	t_env	*new_node;

	if (!env)
		return ;
	current = *env;
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
	if (!*env)
	{
		*env = malloc(sizeof(t_env));
		if (!*env)
			return ;
		(*env)->key = ft_strdup(key);
		(*env)->value = ft_strdup(value);
		(*env)->next = NULL;
		return ;
	}
	last_node = ft_lstlast(*env);
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
				set_env(&built_in->env, dividing_args[0], dividing_args[1]);
				free_spliting(dividing_args);
			}
			else
				set_env(&built_in->env, args[i], NULL);
			i++;
		}
	}
}