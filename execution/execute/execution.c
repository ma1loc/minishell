#include "mini_shell.h"

// >>> clear command not working with msg
    //  minishell$ clear
    //  TERM environment variable not set. to set litter on
// internal and external
// >>> new one <<<
// >>> set the exit status here <<<
void    execute_external(t_tree *tree, t_setup *setup)
{
    pid_t     pid;
    int     status;
    (void)tree;     // >>> to remove litter on.

    setup->cmd_path = path_resolver(setup);
    if (!setup->cmd_path)
    {
        ft_perror(setup ,"Command not found\n", CMD_NOT_FOUND); // >>> exit status to set litter on
        return;
    }
    pid = fork();
    if (pid == -1)
    {
        ft_perror(setup, NULL, EXIT_FAILURE);
        return;
    }    
    if (pid == 0)
    {
        // >>> child process
        if (execve(setup->cmd_path, setup->cmd->args, setup->envp) == -1)
            ft_perror(setup, NULL, EXIT_FAILURE);
        exit(EXIT_FAILURE);
    }
    else
    {
        // >>> parent process
        waitpid(pid, &status, 0);
        // >>> save exit status
        if (WIFEXITED(status))
            setup->exit_stat = WEXITSTATUS(status); // >>> to check litter on
	}
}

void    execute_command(t_tree *tree, t_setup *setup)
{
    if (!tree)
        return ;
    else if (is_built_in(tree->name))
    {
        execute_internal(tree->cmd, setup);
        return ;
    }
    else
    {
        execute_external(tree, setup);
        return ;
    }
}

void handle_redirections(t_tree *tree, t_setup *setup)
{
    if (tree->cmd->redirections->type == TOKEN_HERDOC)
        heredoc(tree, setup);
    else if (tree->cmd->redirections->type == TOKEN_RED_IN)
        red_input(tree, setup);
    else if (tree->cmd->redirections->type == TOKEN_APPEND)
        red_append(tree, setup);
    else if (tree->cmd->redirections->type == TOKEN_RED_OUT)
        red_output(tree, setup);
}

void    execution(t_tree *tree, t_setup *setup)
{
    if (tree->type == TOKEN_WORD)
    {

        if(tree->cmd->redirections == NULL)
            execute_command(tree, setup);
        else
			handle_redirections(tree, setup);
    }
    else if (tree->type == TOKEN_PIPE)
        execute_pipe(tree, setup);
}
