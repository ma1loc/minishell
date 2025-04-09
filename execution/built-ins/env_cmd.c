#include "mini_shell.h"

void	seting_env(t_env *new_node, char **split_env, t_gc *gc)
{
    new_node->key = ft_strdup(split_env[0], gc);
    if (!new_node->key)
		allocation_failed_msg(gc);
    if (split_env[1])
    {
        new_node->value = ft_strdup(split_env[1], gc);
        if (!new_node->value)
			allocation_failed_msg(gc);
    }
    else
        new_node->value = NULL;
}

t_env *init_env(char **env, t_env *env_list, t_gc *gc)
{
    t_env *new_node;
    char **split_env;
    int i;
    
    i = 0;
    while (env[i])
    {
        new_node = gc_malloc(gc, sizeof(t_env));
        if (!new_node)
            allocation_failed_msg(gc);
        split_env = ft_split(env[i], '=', gc);
        if (!split_env)
			allocation_failed_msg(gc);
        seting_env(new_node, split_env, gc);
        new_node->next = NULL;
        ft_lstadd_back(&env_list, new_node);
        i++;
    }
    return (env_list);
}

void env_cmd(t_setup *setup)
{
    t_env *tmp_env;
    
    tmp_env = setup->env;
    if (!setup->env)
        return ;
    if (setup->cmd->args[1])
    {
        ft_perror(setup, "env: too many arguments\n", EXIT_FAILURE);
        return ;
    }
    while (tmp_env)
    {
        if (tmp_env->value)
            printf("%s=%s\n", tmp_env->key, tmp_env->value);
        tmp_env = tmp_env->next;
    }
    setup->exit_stat = 0;
}
