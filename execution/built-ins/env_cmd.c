#include "../../srcs/mini_shell.h"

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

// >>> init the env
t_env	*init_env(char **env)
{
    t_env   *env_list;
	t_env	*new_node;
    char    **env_split;
    int     i;

    i = 0;
	env_list = NULL;
	while (env[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		env_split = ft_split(env[i], '=');
		if (!env_split)
			return (free(new_node) ,NULL);
		new_node->key = ft_strdup(env_split[0]);
		if (env_split[1])
			new_node->value = ft_strdup(env_split[1]);
		else
			new_node->value = NULL;
		new_node->next = NULL;
		free_the_spliting(env_split);
		ft_lstadd_back(&env_list, new_node);
		i++;
	}
    return env_list;
}

// print all env
void	env_cmd(t_env *env_list)
{
	if (!env_list)
		return ;
    while (env_list)
	{
		printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
}
