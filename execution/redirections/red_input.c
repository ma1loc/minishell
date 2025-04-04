#include "mini_shell.h"

int red_input(t_setup *setup,t_tree *tree, t_redirections *redirection)
{
	int		in_fd;

    in_fd = open(redirection->file_name, O_RDONLY);
    if (in_fd < 0)
        return (ft_perror(setup, NULL, EXIT_FAILURE), -1);
    if (tree->cmd->name == NULL)
        return (close(in_fd), 1);
    else
    {
        if (dup2(in_fd, STDIN_FILENO) == -1)
            return (close(in_fd), ft_perror(setup, NULL, EXIT_FAILURE), -1);
        close(in_fd);
    }
    return (0);
}
