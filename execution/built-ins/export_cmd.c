#include "mini_shell.h"

int export_key_only(t_setup *setup, char *key)
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
        allocation_failed_msg();
    new_node->key = ft_strdup(key);
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

void	set_env_update(t_setup *setup, char *arg)
{
	int		len;
	char	*key;
	char	*value;
	char	*get_char;

	len = ft_strlen(arg);
	get_char = ft_strchr(arg, '=');
	key = ft_substr(arg, 0, get_char - arg);
	if (!key)
		allocation_failed_msg();
	get_char = ft_strchr(arg, '=');
	value = ft_substr(arg, get_char - arg + 1, len);
	if (!value)
		allocation_failed_msg();
	update_env(setup, key, value);
}


void	set_env_append(t_setup *setup, char *arg)
{
	int		len;
	char	*key;
	char	*value;
	char	*get_char;

	len = ft_strlen(arg);
	get_char = ft_strchr(arg, '+');
	key = ft_substr(arg, 0, get_char - arg);
	if (!key)
		allocation_failed_msg();
	get_char = ft_strchr(arg, '=');
	value = ft_substr(arg, get_char - arg + 1, len);
	if (!value)
		allocation_failed_msg();
	append_to_env(setup, key, value);
}

// the parsing expand
void	handle_export_argument(t_setup *setup, char *arg)
{
	char			*key;
	char			*value;
	t_export_type	type;
	
	key = NULL;
	value = NULL;
	type = get_export_type(arg);
	if (type == APPEND_VALUE)
		set_env_append(setup, arg);
	else if (type == ASSIGN_VALUE)
		set_env_update(setup, arg);
	else
	{
		key = ft_strdup(arg);
		export_key_only(setup, key);
	}
	gc_free(gc, key);
	if (value)
		gc_free(gc, value);
}

void	export_cmd(t_setup *setup)
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
			printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
			printf("in export_cmd -> arg => %s\n", args[i]);
			printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
			handle_export_argument(setup, args[i]);
			i++;
        }
    }
}
