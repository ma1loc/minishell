#include "mini_shell.h"

// >>> clear command not working with msg
    //  minishell$ clear
    //  TERM environment variable not set. to set litter on
// internal and external
void execute_external(t_tree *tree, t_setup *setup)
{
    (void)tree;
    int pid;
    setup->cmd_path = path_resolver(setup);
    if (!setup->cmd_path)
        printf("path -> NULL\n"); //    >>> to do litter on
    else
    {
        pid = fork();
        if (pid == -1)
            printf("path -> NULL\n"); //    >>> to do litter on
        if (pid == 0)
        {
            if (execve(setup->cmd_path, setup->cmd->args, setup->envp) == -1)
            {
                printf("failed execve\n"); //  >>> to do litter on
                exit(FAIL);
            }
        }
        else
            waitpid(pid, NULL, 0);
    }
}

void    execute_command(t_tree *tree, t_setup *setup)
{
    if (!tree)
        return ;
    if (is_built_in(tree->name))
    {
        printf(">>> build_in\n");
        execute_internal(tree->cmd, setup);
        return ;
    }
    else
    {
        printf(">>> not build_in\n");
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
