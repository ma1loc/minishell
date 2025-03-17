#include "mini_shell.h"

void create_pipe(int *fds)
{
    if (pipe(fds) == -1)
    {
        ft_perror("pipe failed", 1);
        exit(1);
    }
}

pid_t create_fork()
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
    {
        ft_perror("fork failed", 1);
        exit(1);
    }
    return pid;
}

void left_process(t_tree *left, t_setup *setup, int *fds)
{
    // >>> close read end
    close(fds[0]);
    dup2(fds[1], STDOUT_FILENO);
    close(fds[1]);
    
    if (left)
        execute_tree(left, setup);
    
    exit(0);
}

void right_process(t_tree *right, t_setup *setup, int *fds)
{
    // >>> close write end
    close(fds[1]);
    dup2(fds[0], STDIN_FILENO);
    close(fds[0]);
    
    if (right)
        execute_tree(right, setup);
    
    exit(0);
}

int execute_pipe(t_tree *tree, t_setup *setup)
{
    printf(">>> pipe line\n");
    int fds[2];
    pid_t pid1;
    pid_t pid2;
    int status;

    create_pipe(fds);
    
    // >>> left command (writes to pipe)
    pid1 = create_fork();
    if (pid1 == 0)
        left_process(tree->left, setup, fds);
        
    // >>> right command (reads from pipe)
    pid2 = create_fork();
    if (pid2 == 0)
        right_process(tree->right, setup, fds);

    close(fds[0]);
    close(fds[1]);
    
    waitpid(pid1, NULL, 0);
    waitpid(pid2, &status, 0);

    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    else
        return 1;
}

int execute_tree(t_tree *tree, t_setup *setup)
{
    if (!tree)
        return 0;       
    if (tree->type == TOKEN_WORD)
    {
        execute_command(tree, setup);   // here have the problem
        return 0;
    }
    else if (tree->type == TOKEN_PIPE)
    {
        return execute_pipe(tree, setup);
    }
    
    return 0;
}