#include "mini_shell.h"

void    execute_externals(t_setup *setup, t_gc *gc)
{
    pid_t     pid;
    int     status;

	pid = 0;
    setup->cmd_path = path_resolver(setup, gc);
    if (!setup->cmd_path)
	{
		ft_perror(setup ,"command not found\n", CMD_NOT_FOUND);
		return ;
	}
	pid = set_fork(setup, gc);
    if (pid == 0)
    {
        if (execve(setup->cmd_path, setup->cmd->args, setup->exec_env) == -1)
            ft_perror(setup, NULL, EXIT_FAILURE);
		gc_destroy(gc);
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(pid, &status, 0); // the last arg -> 0 is for waitpid to act normall
        if (WIFEXITED(status))
            setup->exit_stat = WEXITSTATUS(status); // >>> to check later on
	}
}

void	execute_commands(t_tree *tree, t_setup *setup, t_gc *gc)
{
	if (!tree)
		return ;
	else if (is_built_in(tree->name))
	{
		execute_internals(tree->cmd, setup, gc);
		return ;
	}
	execute_externals(setup, gc);
}

void	execution(t_tree *tree, t_setup *setup, t_gc *gc)
{
	if (tree->type == TOKEN_WORD)
	{
		if(tree->cmd->redirections == NULL)
		{
			setup->fork_flag = 1;
			execute_commands(tree, setup, gc);
		}
		else
		{
			setup->fork_flag = 1;
			execute_redirections(tree, setup, gc);
		}
	}
	else if (tree->type == TOKEN_PIPE)
	{
		setup->fork_flag = 0;
		execute_pipes(tree, setup, gc);
	}
	if (setup->heredoc_flag)
		cleanup_heredoc(setup, gc);
	setup->exec_env = update_exec_envp(setup, gc);
	setup->fork_flag = 0;
}
