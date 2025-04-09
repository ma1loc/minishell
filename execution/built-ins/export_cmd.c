#include "mini_shell.h"

// to handel the return of the functions
// int add_new_key_value(t_setup *setup, char *key, char *value)
// ft_perror(setup, "export: memory allocation failed\n", EXIT_FAILURE);

int export_key_only(t_setup *setup, char *key, t_gc *gc)
{
    t_env *new_node;
	t_env *last_node;
    
	if (!is_valid_identifier(key))
	{
		ft_perror(setup, "export: not a valid identifier\n", EXIT_FAILURE);
		return (-1);
	}
    new_node = gc_malloc(gc, sizeof(t_env));
    if (!new_node)
        allocation_failed_msg(gc);
    new_node->key = ft_strdup(key, gc);
    if (!new_node->key)
		allocation_failed_msg(gc);
    new_node->value = NULL;
    new_node->next = NULL;
    if (!setup->env)
        setup->env = new_node;
    else
    {
        last_node = ft_lstlast(setup->env);
        last_node->next = new_node;
    }
    setup->exit_stat = 0;
    return (0);
}


// the parsing expand i have to use it to here
void	handle_export_argument(t_setup *setup, char *arg, t_gc *gc)
{
	char			*key;
	char			*value;
	t_export_type	type;
	
	key = NULL;
	value = NULL;
	type = get_export_type(arg);
	if (type == APPEND_VALUE)
	{
		key = ft_substr(arg, 0, ft_strchr(arg, '+') - arg, gc);
		value = ft_substr(arg, ft_strchr(arg, '=') - arg + 1, ft_strlen(arg), gc);
		append_to_env(setup, key, value, gc);
	}
	else if (type == ASSIGN_VALUE)
	{
		key = ft_substr(arg, 0, ft_strchr(arg, '=') - arg, gc);
		value = ft_substr(arg, ft_strchr(arg, '=') - arg + 1, ft_strlen(arg), gc);
		update_env(setup, key, value, gc);
	}
	else
	{
		key = ft_strdup(arg, gc);
		export_key_only(setup, key, gc);
	}
	free(key);
	if (value)
		free(value);
}


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void	export_cmd(t_setup *setup, t_gc *gc)
{
    char	**args;
    int		i;
    
    i = 1;
    args = setup->cmd->args;
    
    if (!args[i])
        export_display(setup);
    else
    {
        while (args[i])
        {
			handle_export_argument(setup, args[i], gc);
			i++;
        }
    }
}
