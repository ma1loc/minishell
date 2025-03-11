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

t_env	*init_env(char **env, t_setup *set_env)
{
    t_env   *env_list;
	t_env	*new_node;
    int     i;

    i = 0;
	env_list = NULL;
	while (env[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		set_env->env_split = ft_split(env[i], '=');
		if (!set_env->env_split)
			free(new_node);
		new_node->key = ft_strdup(set_env->env_split[0]);
		if (set_env->env_split[1])
			new_node->value = ft_strdup(set_env->env_split[1]);
		else
			new_node->value = NULL;
		new_node->next = NULL;
		free_the_spliting(set_env->env_split);
		ft_lstadd_back(&env_list, new_node);
		i++;
	}
	return (env_list);
}

// print all env
void	env_cmd(t_setup *built_in)
{
	t_env	*current;

	current = built_in->env_list;
	if (!built_in->env_list)
		return ;
    while (current)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}
