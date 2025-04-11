#include "mini_shell.h"

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
			setup->cmd = tree->left->cmd;
            if (tree->left->cmd && tree->left->cmd->redirections)
				execute_redirections(tree->left, setup);
            else
                execute_commands(tree->left, setup);
        }
        else
            execution(tree->left, setup);
    }
    exit(setup->exit_stat);
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
            setup->cmd = tree->right->cmd;
            if (tree->right->cmd && tree->right->cmd->redirections)
				execute_redirections(tree->right, setup);
            else
                execute_commands(tree->right, setup);
        }
        else
            execution(tree->right, setup);
    }
    exit(setup->exit_stat);
}

void    execute_pipes(t_tree *tree, t_setup *setup)
{
    int		fd[2];
    pid_t	pid_1;
    pid_t	pid_2;
    int		status;

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
	if (pid_1 < 0 || pid_2 < 0)
		return (gc_destroy(gc), exit(EXIT_FAILURE), (void)0);
    // >>> wait for both children to finish
    waitpid(pid_1, &status, 0);
    waitpid(pid_2, &status, 0);
	if (WIFEXITED(status))
        setup->exit_stat = WEXITSTATUS(status);
}
