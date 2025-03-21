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
        ft_perror(setup, NULL, FAIL);
        return;
    }    
    if (pid == 0)
    {
        // >>> child process
        if (execve(setup->cmd_path, setup->cmd->args, setup->envp) == -1)
            ft_perror(setup, NULL, FAIL);
        exit(FAIL);
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
        // printf(">>> build_in\n");
        execute_internal(tree->cmd, setup);
        return ;
    }
    else
    {
        // printf(">>> not build_in\n");
        execute_external(tree, setup);
        return ;
    }
}

// >>> if user give just the "<<" put synatx error -> handel it litter on, (exit status of it is 2)
// >>> msg "syntax error near unexpected token" exit status -> 2
// tests -> "ls | << l cat | cat" is valid or not?
void    execution(t_tree *tree, t_setup *setup)
{
    (void)setup;
    // if (tree->cmd->redirections->type == TOKEN_HERDOC) // >>> segv here
    // {
    //     printf("access to heredoc\n");
    //     heredoc(tree, setup);
    // }

    // >>> here i have to update the envp
    if (tree->type == TOKEN_WORD)
    {
        if(tree->cmd->redirections == NULL)
            execute_command(tree, setup);
        else
        {
            if (tree->cmd->redirections->type == TOKEN_HERDOC)
			{
				int i = 0;
				printf("file name -> %s\n", tree->cmd->redirections->file_name);
				printf("tree->cmd->name -> |%s|\n", tree->cmd->name);
				printf("command -> %s\n", tree->cmd->name);
				while (tree->cmd->args[i])
				{
					printf("tree->cmd->args[%d] -> |%s|\n", i, tree->cmd->args[i]);
					i++;
				}
                heredoc(tree, setup);
			}
            else if(tree->cmd->redirections->type == TOKEN_RED_IN)
                red_input(tree, setup);
            else if(tree->cmd->redirections->type == TOKEN_APPEND)
                printf("access to append\n");
            else if(tree->cmd->redirections->type == TOKEN_RED_OUT)
                printf("access to red out\n");
        }
    }
    else if (tree->type == TOKEN_PIPE)
        execute_pipe(tree, setup);
}
