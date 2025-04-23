/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_exec_envp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:06:03 by yanflous          #+#    #+#             */
/*   Updated: 2025/04/23 10:06:06 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	free_old_envp(t_setup *setup)
{
	int	i;

	i = 0;
	while (setup->exec_env[i])
	{
		gc_free(g_gc, setup->exec_env[i]);
		i++;
	}
	gc_free(g_gc, setup->exec_env);
}

int	count_envp(t_env *env)
{
	int		env_len;
	t_env	*current_env;

	env_len = 0;
	current_env = env;
	while (current_env)
	{
		env_len++;
		current_env = current_env->next;
	}
	return (env_len);
}

char	**update_exec_envp(t_setup *setup, t_env *cur_env)
{
	int		envp_len;
	char	**envp_update;
	char	*key;
	char	*full_line;
	int		i;

	if (setup->exec_env)
		free_old_envp(setup);
	envp_len = count_envp(setup->env);
	envp_update = gc_malloc(g_gc, sizeof(char *) * (envp_len + 1));
	if (!envp_update)
		allocation_failed_msg();
	i = 0;
	cur_env = setup->env;
	while (cur_env)
	{
		key = ft_strjoin(cur_env->key, "=");
		full_line = ft_strjoin(key, cur_env->value);
		gc_free(g_gc, key);
		envp_update[i] = full_line;
		cur_env = cur_env->next;
		i++;
	}
	return (envp_update[i] = NULL, envp_update);
}
