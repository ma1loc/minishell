#include "mini_shell.h"

int	red_in_out(t_tree *tree, t_setup *setup, t_redirections *redirection)
{
	int	in_out_fd;

	in_out_fd = open(redirection->file_name, O_CREAT | O_RDONLY, 0644);
	if (in_out_fd == -1)
		return (ft_perror(setup, NULL, EXIT_FAILURE), -1);
	if (tree->cmd->name == NULL)	// check is ther any command
		return (close(in_out_fd), -1);
	else
	{
		if (dup2(in_out_fd, STDIN_FILENO) == -1)
			return (close(in_out_fd), ft_perror(setup, NULL, EXIT_FAILURE), -1);
		close(in_out_fd);
	}
	return (0);
}

int red_input(t_tree *tree, t_setup *setup, t_redirections *redirection)
{
	int in_fd;
    
    in_fd = open(redirection->file_name, O_RDONLY);
    if (in_fd < 0)
        return (ft_perror(setup, NULL, EXIT_FAILURE), -1);
    if (tree->cmd->name == NULL)
        return (close(in_fd), -1);
    else
    {
        if (dup2(in_fd, STDIN_FILENO) == -1)
            return (close(in_fd), ft_perror(setup, NULL, EXIT_FAILURE), -1);
        close(in_fd);
    }
    return (0);
}

int    red_output(t_tree *tree, t_setup *setup, t_redirections *redirections)
{
	int		out_fd;
	
	out_fd = open(redirections->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out_fd < 0)
		return (ft_perror(setup, NULL, EXIT_FAILURE), -1);
	if (tree->cmd->name == NULL)
		return (close(out_fd), -1);
    else
    {
        if (dup2(out_fd, STDOUT_FILENO) == -1)
			return (close(out_fd), ft_perror(setup, NULL, EXIT_FAILURE), -1);
        close(out_fd);
    }
	return (0);
}

int	red_append(t_tree *tree, t_setup *setup, t_redirections *redirection)
{
	int	append_fd;

	append_fd = open(redirection->file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (append_fd == -1)
		return (ft_perror(setup, NULL, EXIT_FAILURE), -1);
	if (tree->cmd->name == NULL)
		return (close(append_fd), -1);
	else
	{
		if (dup2(append_fd, STDOUT_FILENO) == -1)
			return (ft_perror(setup, NULL, EXIT_FAILURE), -1);
		close(append_fd);
	}
	return (0);
}

int		red_heredoc(t_tree *tree, t_setup *setup)
{
    int		i;

    i = setup->i;
	(void)tree;

    if (tree->cmd->name == NULL)
        return (close(setup->heredoc->fd[i]), -1);
    else
    {
        if (dup2(setup->heredoc->fd[i], STDIN_FILENO) == -1)
        {
            close(setup->heredoc->fd[i]);
            return (ft_perror(setup, "Error: dup2 failed\n", EXIT_FAILURE), -1);
        }
        close(setup->heredoc->fd[i]);
    }
    return (0);
}

void	execute_redirections(t_tree *tree, t_setup *setup)
{
	int result;
    int save_stdin;
    int save_stdout;
    t_redirections *current;

	// result = -1;
	result = 0;
	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
    current = tree->cmd->redirections;
    while (current != NULL)
    {
        if (current->type == TOKEN_RED_IN)
            result = red_input(tree, setup, current);
        else if (current->type == TOKEN_RED_OUT)
			result = red_output(tree, setup, current);
		else if (current->type == TOKEN_RED_INOUT)
			result = red_in_out(tree, setup, current);
		else if (current->type == TOKEN_APPEND)
			result = red_append(tree, setup, current);
		else if (current->type == TOKEN_HERDOC)
			result = red_heredoc(tree, setup);
		if (result == -1)
			break;
		current = current->next;
    }
	if (result != -1)
		execute_commands(tree, setup);
    dup2(save_stdin, STDIN_FILENO);
    dup2(save_stdout, STDOUT_FILENO);
    close(save_stdin);
    close(save_stdout);
}
