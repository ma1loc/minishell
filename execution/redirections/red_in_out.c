#include "mini_shell.h"

int	red_in_out(t_setup *setup,t_tree *tree, t_redirections *redirection)
{
	int		in_out_fd;

	in_out_fd = open(redirection->file_name, O_CREAT | O_RDONLY, 0644);
	if (in_out_fd < 0)
		return (ft_perror(setup, NULL, EXIT_FAILURE), -1);
	if (tree->cmd->name == NULL)
		return (close(in_out_fd), 1);
	else
	{
		if (dup2(in_out_fd, STDIN_FILENO) == -1)
			return (close(in_out_fd), ft_perror(setup, NULL, EXIT_FAILURE), -1);
		close(in_out_fd);
	}
	return (0);
}
