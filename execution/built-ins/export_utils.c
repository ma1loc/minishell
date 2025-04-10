# include "mini_shell.h"

void	add_to_env(t_setup *setup, char *key, char *value)
{
	t_env	*env;
	
	env = ft_lstlast(setup->env);
	if (!env)
	{
		setup->env = gc_malloc(gc, sizeof(t_env));
		env = setup->env;
	}
	else
	{
		env->next = gc_malloc(gc, sizeof(t_env));
		env = env->next;
	}
	if (!env)
		allocation_failed_msg(gc);
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	env->next = NULL;
	if (!env->key || !env->value)
		allocation_failed_msg(gc);
}

void	update_env(t_setup *setup, char *key, char *value)
{
	t_env	*env;

	if (!is_valid_identifier(key))
	{
		ft_perror(setup, "export: not a valid identifier\n", EXIT_FAILURE);
		return ;
	}
	env = get_env_key(setup, key);
	if (env)
	{
		if (env->value)
			gc_free(gc, env->value);
		env->value = ft_strdup(value);
		if (!env->value)
			allocation_failed_msg(gc);
	}
	else
		add_to_env(setup, key, value);
}

void	append_to_env(t_setup *setup, char *key, char *value)
{
	t_env	*env;
	char	*new_value;

	new_value = NULL;
	env = get_env_key(setup, key);
	if (env)
	{
		if (env->value)
		{
			new_value = ft_strjoin(env->value, value);
			if (!new_value)
				allocation_failed_msg(gc);
			gc_free(gc, env->value);
			env->value = new_value;
		}
		else
			env->value = ft_strdup(value);
	}
	else
		update_env(setup, key, value);
}
