# include "mini_shell.h"

void    free_old_envp(t_setup *setup)
{
    int i;

    i = 0;
    while (setup->exec_env[i])
    {
        gc_free(gc, setup->exec_env[i]);
        i++;
    }
    gc_free(gc, setup->exec_env);  // Free the envp array itself
}

int     count_envp(t_env *env)
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

char    **update_exec_envp(t_setup *setup)
{
    int     envp_len;
    char    **envp_update;
	t_env   *current_env;
    char    *key;
    char    *full_line;
    int     i;

    if (setup->exec_env)
        free_old_envp(setup);
    envp_len = count_envp(setup->env);
    envp_update = gc_malloc(gc, sizeof(char *) * (envp_len + 1));
    if (!envp_update)
        allocation_failed_msg(gc);
    i = 0;
    current_env = setup->env;
    while (current_env)
    {
        key = ft_strjoin(current_env->key, "=");
        full_line = ft_strjoin(key, current_env->value);
        gc_free(gc, key);
        envp_update[i] = full_line;
        current_env = current_env->next;
        i++;
    }
    return (envp_update[i] = NULL, envp_update);
}
