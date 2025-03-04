#include "../../srcs/mini_shell.h"


// // Manage env variables (`export`, `unset`)
// // copy the env to a structer

// // first count how many env in the env
// int		env_len(char **env)
// {
// 	int	env_count;

// 	env_count = 0;
// 	while (env[env_count])
// 		env_count++;
// 	return (env_count);
// }

// void	*fill_env(char *env);

// t_env	*set_env(char *env, int key, int value)
// {
// 	t_env	*new_env;

// 	new_env = malloc(sizeof(t_env));
// 	if (!new_env)
// 		return (NULL);
// 	new_env->key = malloc(sizeof(key));
// 	if (!new_env)
// 		return (NULL);
// 	new_env->value = malloc(sizeof(value));
// 	if (!new_env)
// 		return (NULL);
	
// 	return (new_env);
// }

// Manage env variables (`export`, `unset`)
// copy the env to a structer

// first count how many env in the env
// int		env_len(char **env)
// {
// 	int	env_count;

// 	env_count = 0;
// 	while (env[env_count])
// 		env_count++;
// 	return (env_count);
// }

// // void	*fill_env(char *env);

// t_env	*set_env(char *env, int key, int value)
// {
// 	(void)env;
// 	t_env	*new_env;

// 	new_env = malloc(sizeof(t_env));
// 	if (!new_env)
// 		return (NULL);
// 	new_env->key = malloc(sizeof(key));
// 	if (!new_env)
// 		return (NULL);
// 	new_env->value = malloc(sizeof(value));
// 	if (!new_env)
// 		return (NULL);
	
// 	return (new_env);
// }
// >>>>>>> main

// t_env	*env_split(char	**env)
// {
// 	int		key_len;
// 	int		value_len;
// 	int		env_count;
// 	t_env	*list_env;
// 	int 	i;

// 	key_len = 0;
// 	value_len = 0;
// 	while (env[key_len] && env[key_len] != '=')
// 		key_len++;
// 	while (env[key_len + value_len])
// 		value_len++;
// 	i = 0;
// 	env_count = env_len(env);
// 	while (i < env_count)
// 	{
// 		list_env = set_env(env[i], key_len, value_len);
// 		list_env = list_env->next;
// 		i++;
// 	}
// 	return (list_env);
// }
