#include "mini_shell.h"

void    execute_externals(t_setup *setup)
{
    pid_t     pid;
    int     status;

    setup->cmd_path = path_resolver(setup);
    if (!setup->cmd_path)
		return(ft_perror(setup ,"Command not found\n", CMD_NOT_FOUND), (void)0); // >>> exit status to set litter on
        
    pid = fork();
    if (pid == -1)
    {
        ft_perror(setup, NULL, EXIT_FAILURE);
        return;
    }    
    if (pid == 0)
    {
        if (execve(setup->cmd_path, setup->cmd->args, setup->envp) == -1)
            ft_perror(setup, NULL, EXIT_FAILURE);
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(pid, &status, 0); // the last arg -> 0 is for waitpid to act normall
        if (WIFEXITED(status))
            setup->exit_stat = WEXITSTATUS(status); // >>> to check litter on
	}
}

void	execute_commands(t_tree *tree, t_setup *setup)
{
	if (!tree)
		return ;
	else if (is_built_in(tree->name))
	{
		execute_internals(tree->cmd, setup);
		return ;
	}
	else
	{
		execute_externals(setup);
		return ;
	}
}

void	execution(t_tree *tree, t_setup *setup)
{
	if (tree->type == TOKEN_WORD)
	{
		if(tree->cmd->redirections == NULL)
			execute_commands(tree, setup);
		else
			execute_redirections(tree, setup);
	}
	else if (tree->type == TOKEN_PIPE)
		execute_pipes(tree, setup);
}
