# include "mini_shell.h"

void export_display(t_setup *setup)
{
    t_env *tmp_env;
    
    tmp_env = setup->env;
    if (!setup->env)
        return;
    
    while (tmp_env)
    {
        printf("declare -x %s", tmp_env->key);
        if (tmp_env->value)
            printf("=\"%s\"", tmp_env->value);
        printf("\n");
        tmp_env = tmp_env->next;
    }
    setup->exit_stat = 0;
}

t_export_type	get_export_type(char *arg)
{
	char	*equal;
	char	*plus;
	
	plus = ft_strchr(arg, '+');
	equal = ft_strchr(arg, '=');
	if (!equal)
		return (KEY_ONLY);
	if (plus && plus + 1 == equal)
		return (APPEND_VALUE);
	return (ASSIGN_VALUE);
}

t_env	*get_env_key(t_setup *setup, char *key)
{
	t_env	*env;

	env = setup->env;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}