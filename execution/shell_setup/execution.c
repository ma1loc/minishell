#include "mini_shell.h"

// >>> clear command not working with msg
    //  minishell$ clear
    //  TERM environment variable not set. to set litter on
// internal and external
// >>> new one <<<
void    execute_external(t_tree *tree, t_setup *setup)
{
    int     pid;
    int     status;
    (void)tree;

    setup->cmd_path = path_resolver(setup);
    if (!setup->cmd_path)
    {
        printf("Command not found: %s\n", setup->cmd->name); // >>> exit status to set litter on
        return;
    }
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }    
    if (pid == 0)
    {
        // >>> child process
        if (execve(setup->cmd_path, setup->cmd->args, setup->envp) == -1) {
            perror("execve");
            exit(EXIT_FAILURE); // >>> exit status to set litter on
        }
        // >>> if not execve succeed
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
    if (is_built_in(tree->name))
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

void    execution(t_tree *tree, t_setup *setup)
{
    if (tree->type == TOKEN_WORD)
        execute_command(tree, setup);
    else if (tree->type == TOKEN_PIPE)
        execute_pipe(tree, setup);
}
