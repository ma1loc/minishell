#include "mini_shell.h"

void    set_pipe(t_setup *setup, int *fd)
{
    if (pipe(fd) == -1)
    {
        ft_perror(setup, NULL, EXIT_FAILURE);
        return;
    }
}

pid_t    set_first_fork(t_setup  *setup, int *fd)
{
    pid_t pid1;

    pid1 = fork();
    if (pid1 < 0)
    {
        close(fd[0]);
        close(fd[1]);
        ft_perror(setup, NULL, EXIT_FAILURE);
        return (-1);
    }
    return (pid1);
}

pid_t    set_second_fork(t_setup  *setup, pid_t pid_1, int *fd)
{
    pid_t   pid_2;
    
    pid_2 = fork();
    if (pid_2 < 0)
    {
        close(fd[0]);
        close(fd[1]);
        waitpid(pid_1, NULL, 0);  // >>> wait for first child
        ft_perror(setup, NULL, EXIT_FAILURE);
        return (-1);
    }
    return (pid_2);
}

void first_child_process(t_setup *setup, t_tree *tree, int *fd)
{
    close(fd[0]);
    if (dup2(fd[1], STDOUT_FILENO) == -1)
    {
        ft_perror(setup, NULL, EXIT_FAILURE);
        exit(EXIT_FAILURE);
    }
    close(fd[1]);
    
    if (tree->left)
    {
        if (tree->left->type == TOKEN_WORD)
        {
            if (tree->left->cmd && tree->left->cmd->redirections)
            {
				// setup->cmd->redirections = tree->cmd->redirections->next;
                printf("it's a redirection\n");
				setup->cmd = tree->left->cmd;
				execute_redirections(tree->left, setup);
            }
            else
            {
                setup->cmd = tree->left->cmd;
                execute_commands(tree->left, setup);
            }
        }
        else
            execution(tree->left, setup);
    }
    exit(EXIT_SUCCESS);
}

void second_child_process(t_setup *setup, t_tree *tree, int *fd)
{
    close(fd[1]);
    if (dup2(fd[0], STDIN_FILENO) == -1)
    {
        ft_perror(setup, NULL, EXIT_FAILURE);
        exit(EXIT_FAILURE);
    }
    close(fd[0]);
    
    if (tree->right)
    {
        if (tree->right->type == TOKEN_WORD)
        {
            if (tree->right->cmd && tree->right->cmd->redirections)
            {
				// setup->cmd->redirections = tree->cmd->redirections->next;
                setup->cmd = tree->right->cmd;
				execute_redirections(tree->right, setup);
            }
            else
            {
                setup->cmd = tree->right->cmd;
                execute_commands(tree->right, setup);
            }
        }
        else
            execution(tree->right, setup);
    }
    exit(EXIT_SUCCESS);
}

void    execute_pipes(t_tree *tree, t_setup *setup)
{
    int fd[2];
    pid_t pid_1;
    pid_t pid_2;
    int status;
    
    // >>> seting the pipe
    set_pipe(setup, fd);
    // >>> first child process left side
    pid_1 = set_first_fork(setup, fd);
    if (pid_1 == 0)
        first_child_process(setup, tree, fd);
    // >>> second child process right side
    pid_2 = set_second_fork(setup, pid_1, fd);
    if (pid_2 == 0)
        second_child_process(setup, tree, fd);
    // >>> parent process
    close(fd[0]);
    close(fd[1]);
    // >>> wait for both children to finish
    waitpid(pid_1, &status, 0);
    waitpid(pid_2, &status, 0);
}
