#include "mini_shell.h"

void	free_the_spliting(char	**split)
{
	int	i;
	
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

// t_env	*init_env(char **env, t_setup *set_env)
t_env	*init_env(char **env, t_env *env_list)
{
    // t_env   *env_list;
	t_env	*new_node;
	char	**split_env;

    int     i;

    i = 0;
	while (env[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		split_env = ft_split(env[i], '=');
		if (!split_env)
			free(new_node);
		new_node->key = ft_strdup(split_env[0]);
		if (split_env[1])
			new_node->value = ft_strdup(split_env[1]);
		else
			new_node->value = NULL;
		new_node->next = NULL;
		free_the_spliting(split_env);
		ft_lstadd_back(&env_list, new_node);
		i++;
	}
	return (env_list);
}

void	env_cmd(t_setup *built_in)
{
	t_env	*current;

	current = built_in->env;
	if (!built_in->env)
		return ;
    while (current)
	{
		if (ft_strcmp(built_in->cmd->name, "export") == 0)
		{
			printf("declare -x ");
			printf("%s=\"%s\"\n", current->key, current->value);
		}
		else
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}
