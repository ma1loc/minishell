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

<<<<<<< HEAD
t_env	*init_env(char **env, t_set_env *set_env)
{
    t_env   *env_list;
	t_env	*new_node;
=======
<<<<<<< HEAD
// >>> init the env
=======
// >>> unset && env 
// >>> initilization of the env
>>>>>>> 4b13520 (update)
t_env	*init_env(char **env)
{
    t_env   *env_list;
	t_env	*new_node;
    char    **env_split;
>>>>>>> 0ce570e13e4b0b223063194c26e845647d18e9d8
    int     i;

    i = 0;
	env_list = NULL;
	while (env[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
<<<<<<< HEAD
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
void	env_cmd(t_set_env *built_in)
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
=======
		env_split = ft_split(env[i], '=');
		if (!env_split)
			return (free(new_node) ,NULL);
		new_node->key = ft_strdup(env_split[0]);
<<<<<<< HEAD
		if (env_split[1])
			new_node->value = ft_strdup(env_split[1]);
		else
			new_node->value = NULL;
=======
		new_node->value = ft_strdup(env_split[1]);
>>>>>>> 4b13520 (update)
		new_node->next = NULL;
		free_the_spliting(env_split);
		ft_lstadd_back(&env_list, new_node);
		i++;
	}
    return env_list;
}

// print all env
<<<<<<< HEAD
void	env_cmd(t_env *env_list)
=======
void	print_env(t_env *env_list)
>>>>>>> 4b13520 (update)
{
	if (!env_list)
		return ;
    while (env_list)
	{
		printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
}
<<<<<<< HEAD
=======

void	env_cmd(char **env)
{
    t_env	*env_header;

	env_header = init_env(env);
	print_env(env_header);
}
>>>>>>> 4b13520 (update)
>>>>>>> 0ce570e13e4b0b223063194c26e845647d18e9d8
