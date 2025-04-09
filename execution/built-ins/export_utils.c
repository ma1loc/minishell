# include "mini_shell.h"

// >>> Key must start with letter or underscore
// >>> bash: export: `5': not a valid identifier
// >>> bash: export: `h-ello': not a valid identifier
// minishell$ export PATH=/bin/
// minishell$ ls
// Command not found
// minishell$ 
// export a+="hello_world" >>> to handel it
// export a="" >>> to handel it
// export: `a++=l': not a valid identifier
// export: `a+l': not a valid identifier
// yanflous@e2r5p4:/home/yanflous$ export a+=+=+=l
// yanflous@e2r5p4:/home/yanflous$ export a+=+ =+=l
// bash: export: `=+=l': not a valid identifier
// export SHLVL=-198892983983928398293982838928392809878979878
// yanflous@e2r5p4:/home/yanflous$ export SHLVL=1000 
// yanflous@e2r5p4:/home/yanflous$ exit^C            
// yanflous@e2r5p4:/home/yanflous$ bash
// bash: warning: shell level (1001) too high, resetting to 1
// parsing the value of the exporot key to expand
//	'nothing'->0 '='->1 '+='->2 'error->-1'

// to fix the allocation
void	update_env(t_setup *setup, char *key, char *value, t_gc *gc)
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
		env->value = ft_strdup(value, gc);
		if (!env->value)
			allocation_failed_msg(gc);
	}
	else
	{
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
		env->key = ft_strdup(key, gc);
		env->value = ft_strdup(value, gc);
		env->next = NULL;
		if (!env->key || !env->value)
			allocation_failed_msg(gc);
	}
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void	append_to_env(t_setup *setup, char *key, char *value, t_gc *gc)
{
	t_env	*env;
	char	*new_value;

	new_value = NULL;
	env = get_env_key(setup, key);
	if (env)
	{
		if (env->value)
		{
			new_value = ft_strjoin(env->value, value, gc);
			if (!new_value)
				allocation_failed_msg(gc);
			gc_free(gc, env->value);
			env->value = new_value;
		}
		else
			env->value = ft_strdup(value, gc);
	}
	else
		update_env(setup, key, value, gc);
}
