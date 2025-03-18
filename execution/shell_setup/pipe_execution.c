#include "mini_shell.h"

void    set_pipe(t_setup *setup, int *fd)
{
    if (pipe(fd) == -1)
    {
        // >>> set the exit status
        ft_perror(setup, "Error: pipe failed\n", FAIL);
        return;
    }
}

pid_t    set_first_fork(t_setup  *setup, int *fd)
{
    pid_t pid1;

    pid1 = fork();
    if (pid1 < 0)
    {
        perror("fork");
        close(fd[0]);
        close(fd[1]);
        ft_perror(setup, NULL, FAIL);
        return (-1);
    }
    return (pid1);
}
// >>> new one <<<
pid_t    set_second_fork(t_setup  *setup, pid_t pid_1, int *fd)
{
    pid_t   pid_2;
    
    pid_2 = fork();
    if (pid_2 < 0)
    {
        perror("fork");
        close(fd[0]);
        close(fd[1]);
        waitpid(pid_1, NULL, 0);  // >>> wait for first child
        ft_perror(setup, NULL, FAIL);
        return (-1);
    }
    return (pid_2);
}

void    first_child_process(t_setup *setup, t_tree *tree, int *fd)
{
    // >>> child process - execute left command
    // >>> close read end, redirect stdout to pipe write end
    close(fd[0]);
    if (dup2(fd[1], STDOUT_FILENO) == -1)
    {
        perror("dup2");
        ft_perror(setup, NULL, FAIL);
        exit(FAIL);
    }
    close(fd[1]);
    if (tree->left)
    {
        if (tree->left->type == TOKEN_WORD)
        {
            setup->cmd = tree->left->cmd;
            execute_command(tree->left, setup);
        }
        else
            execution(tree->left, setup);
    }
    exit(EXIT_SUCCESS);
}

void    second_child_process(t_setup *setup, t_tree *tree, int *fd)
{
        // >>> child process execute right command
        // >>> close write end, redirect stdin to pipe read end
        close(fd[1]);
        if (dup2(fd[0], STDIN_FILENO) == -1)
        {
            perror("dup2");
            ft_perror(setup, NULL, FAIL);
            exit(FAIL);
        }
        close(fd[0]);
        
        if (tree->right)
        {
            if (tree->right->type == TOKEN_WORD)
            {
                setup->cmd = tree->right->cmd;
                execute_command(tree->right, setup);
            }
            else
                execution(tree->right, setup);
        }
        exit(EXIT_SUCCESS);
}

void    execute_pipe(t_tree *tree, t_setup *setup)
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
