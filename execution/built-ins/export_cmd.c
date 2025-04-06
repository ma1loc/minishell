#include "mini_shell.h"

// >>> Key must start with letter or underscore
// >>> bash: export: `5': not a valid identifier
// >>> bash: export: `h-ello': not a valid identifier

// minishell$ export PATH=/bin/
// minishell$ ls
// Command not found
// minishell$ 
// export a+="hello_world" >>> to handel it
// export a="" >>> to handel it

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

int update_key_value(t_setup *setup, t_env *current, char *key, char *value)
{
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            if (value == NULL)
                return (0);		// >>> Key exists but no value to update
            
            free(current->value);
            current->value = ft_strdup(value);
            if (!current->value)
            {
                ft_perror(setup, "export: memory allocation failed\n", EXIT_FAILURE);
                return (-1);
            }
            return (0);
        }
        current = current->next;
    }
    return (1); // >>> key not found
}

int add_new_key_value(t_setup *setup, char *key, char *value)
{
    t_env *new_node;
    
    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return (ft_perror(setup, "export: memory allocation failed\n", EXIT_FAILURE), -1);

    new_node->key = ft_strdup(key);
    if (!new_node->key)
    {
        free(new_node);
        return (ft_perror(setup, "export: memory allocation failed\n", EXIT_FAILURE), -1);
    }
    
    if (value)
    {
        new_node->value = ft_strdup(value);
        if (!new_node->value)
        {
            free(new_node->key);
            free(new_node);
            return (ft_perror(setup, "export: memory allocation failed\n", EXIT_FAILURE), -1);
        }
    }
    else
        new_node->value = NULL;
    new_node->next = NULL;
    
    // handle the case where env list is empty
    if (!setup->env)
        setup->env = new_node;
    else
    {
        t_env *last_node = ft_lstlast(setup->env);
        last_node->next = new_node;
    }
    
    setup->exit_stat = 0;
    return (0);
}

void set_env(t_setup *setup, char *key, char *value)
{
    int status;
    
    if (!key)
        return;
    
    if (!is_valid_identifier(key))
    {
        ft_perror(setup, "export: not a valid identifier\n", EXIT_FAILURE);
        return;
    }
    
    if (!setup->env)
        status = add_new_key_value(setup, key, value);
    else
    {
        status = update_key_value(setup, setup->env, key, value);
        if (status == 1) // >>> key not found
            status = add_new_key_value(setup, key, value);
    }
}

void export_cmd(t_setup *setup)
{
    char **args;
    char **dividing_args;
    int i;
    
    i = 1;
    args = setup->cmd->args;
    
    if (!args[i])
        export_display(setup);
    else
    {
        while (args[i])
        {
			printf("args -> %s\n", args[i]);
            if (ft_strchr(args[i], '='))
            {
                dividing_args = ft_split(args[i], '=');
				printf("dividing_args[0] -> %s\n", dividing_args[0]);
				printf("dividing_args[1] -> %s\n", dividing_args[1]);
                if (!dividing_args)
                {
                    ft_perror(setup, "export: memory allocation failed\n", EXIT_FAILURE);
                    return;
                }
                set_env(setup, dividing_args[0], dividing_args[1]);
                free_the_spliting(dividing_args);
            }
            else
                set_env(setup, args[i], NULL);
            i++;
        }
    }
}
