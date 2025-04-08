# include "mini_shell.h"

t_setup  *init_setup_struct()
{
    t_setup  *setup;

	setup = malloc(sizeof(t_setup));
	if (!setup)
        return (NULL);
	setup->i = 0;
    setup->input = NULL;
    setup->env = NULL;
    setup->token = NULL;
    setup->cmd = NULL;
	setup->tree = NULL;
    setup->pwd = NULL;
    setup->oldpwd = NULL;
    setup->cmd_path = NULL;
    setup->envp = NULL;
    setup->exit_stat = 0;
	setup->heredoc = NULL;
	setup->gc = NULL;
	// set_env->idx_fds = 0;
    return (setup);
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

// void	update_env(t_setup *setup, char *key, char *value)
// >>> to check to replace it with other func
void	set_env(t_setup *setup, char *key, char *value)
{
    int status;
    
    if (!key || !setup)
        return;
    
    if (!is_valid_identifier(key))
    {
        ft_perror(setup, "export: not a valid identifier\n", EXIT_FAILURE);
        return;
    }    
    else
    {
        status = update_key_value(setup, setup->env, key, value);
        if (status == 1) // >>> key not found
            status = export_key_only(setup, key);
    }
}

// >>> setup the env of the minishell
// return NULL here
t_setup *shell_env_setup(char **env)
{
    t_setup  *setup;

    setup = init_setup_struct();
    if (!setup)
		ft_perror(setup, "Error: memory allocation failed\n", EXIT_FAILURE);
    setup->env = init_env(env, setup->env);
    if (!setup->env)
		ft_perror(setup, "Error: failed to set env\n", EXIT_FAILURE); // to free latter on
	setup->heredoc = malloc(sizeof(t_heredoc));
	if (!setup->heredoc)
		return (NULL);
	setup->heredoc->delimiter = NULL;
	ft_memset(setup->heredoc->fd, 0, sizeof(setup->heredoc->fd));
	ft_memset(setup->heredoc->file_name, 0, sizeof(setup->heredoc->file_name));
	get_pwd(setup);
    set_env(setup, "OLDPWD", setup->pwd);	// to check later on

    return (setup);
}
