#include "mini_shell.h"

int set_env(t_env *new_node, char **split_env)
{
    new_node->key = ft_strdup(split_env[0]);
    if (!new_node->key)
    {
        free(new_node);
        free_the_spliting(split_env);
        return (-1);
    }
    if (split_env[1])
    {
        new_node->value = ft_strdup(split_env[1]);
        if (!new_node->value)
        {
            free(new_node->key);
            free(new_node);
            free_the_spliting(split_env);
            return (-1);
        }
    }
    else
        new_node->value = NULL;
    return (0);
}

t_env *init_env(char **env, t_env *env_list)
{
    t_env *new_node;
    char **split_env;
    int i;
    
    i = 0;
    while (env[i])
    {
        new_node = malloc(sizeof(t_env));
        if (!new_node)
        {
            free_env_list(env_list);
            return (NULL);
        }
        split_env = ft_split(env[i], '=');
        if (!split_env)
        {
            free(new_node);
            free_env_list(env_list);
            return (NULL);
        }
        if (set_env(new_node, split_env) == -1)
        {
            free_env_list(env_list);
            return (NULL);
        }
        new_node->next = NULL;
        free_the_spliting(split_env);
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
        return;
    if (setup->cmd->args[1])
    {
        ft_perror(setup, "env: too many arguments\n", EXIT_FAILURE);
        setup->exit_stat = 1;
        return;
    }
    while (tmp_env)
    {
        if (tmp_env->value) // Only print entries with values
            printf("%s=%s\n", tmp_env->key, tmp_env->value);
        tmp_env = tmp_env->next;
    }
    setup->exit_stat = 0;
}
