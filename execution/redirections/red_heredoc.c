#include "mini_shell.h"

// >>> the heredoc function open an alrady open file to read form it
// >>> here i have to get the last heredoc file to take the input form it


int	red_heredoc(t_setup *setup, t_tree *tree)
{
    int		i;

    i = setup->i;
    if (tree->cmd->name == NULL)
        return (close(setup->heredoc->fd[i]), 1);
    else
    {
        if (dup2(setup->heredoc->fd[i], STDIN_FILENO) == -1)
        {
            close(setup->heredoc->fd[i]);
            return (ft_perror(setup, "Error: dup2 failed\n", EXIT_FAILURE), -1);
        }
        close(setup->heredoc->fd[i]);
    }
	setup->i++;
    return (0);
}
