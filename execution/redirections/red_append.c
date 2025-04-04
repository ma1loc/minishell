#include "mini_shell.h"

int	red_append(t_setup *setup, t_tree *tree, t_redirections *redirection)
{
	int		append_fd;

	tree = setup->tree;
	append_fd = open(redirection->file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (append_fd == -1)
		return (ft_perror(setup, NULL, EXIT_FAILURE), -1);
	if (tree->cmd->name == NULL)
		return (close(append_fd), 1);
	else
	{
		if (dup2(append_fd, STDOUT_FILENO) == -1)
			return (ft_perror(setup, NULL, EXIT_FAILURE), -1);
		close(append_fd);
	}
	return (0);
}
