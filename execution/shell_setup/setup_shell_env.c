# include "mini_shell.h"

t_setup	*init_setup(t_gc *gc)
{
	t_setup	*setup;

	setup = gc_malloc(gc, sizeof(t_setup));
	if (!setup)
		allocation_failed_msg(gc);
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
	setup->exec_env = NULL;	// >>> for the execve();
	setup->exit_stat = 0;
	setup->heredoc = NULL;
	return (setup);
}

// >>> setup the env of the minishell
// return NULL here
t_setup	*shell_env_setup(char **env, t_gc *gc)
{
    t_setup	*setup;

	setup = init_setup(gc);
	setup->env = init_env(env, setup->env, gc);
	setup->exec_env = update_exec_envp(setup, gc);
	setup->heredoc = gc_malloc(gc, sizeof(t_heredoc));
	if (!setup->heredoc)
		allocation_failed_msg(gc);
	setup->heredoc->delimiter = NULL;
	ft_memset(setup->heredoc->fd, 0, sizeof(setup->heredoc->fd));
	ft_memset(setup->heredoc->file_name, 0, sizeof(setup->heredoc->file_name));
	get_pwd(setup, gc);
	update_env(setup, "PWD", setup->pwd, gc);
	update_env(setup, "OLDPWD", setup->pwd, gc);
	return (setup);
}
