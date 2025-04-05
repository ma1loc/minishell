# include "mini_shell.h"

void	loding_heredoc(t_setup *setup)
{
	char	*input;

	while (true)
	{
		input = readline("heredoc> ");
		if (input == NULL || ft_strcmp(input, setup->heredoc->delimiter) == 0)
		{
			free(input);
			break;
		}
		write(setup->heredoc->fd[setup->i], input, ft_strlen(input));
		write(setup->heredoc->fd[setup->i], "\n", 1);
		free(input);
	}
}

void	get_delimiter(t_setup *setup, t_redirections *redirection)
{
	if (setup->heredoc->delimiter)
		free(setup->heredoc->delimiter);

	setup->heredoc->delimiter = ft_strdup(redirection->file_name);
	redirection = redirection->next;
	return ;
}

int	get_heredoc_fds(t_setup *setup, t_redirections *red)
{
	char	*file_name;
	int		i;

	i = setup->i;
	file_name = get_file_name(setup);
	setup->heredoc->file_name[setup->i] = ft_strdup(file_name);
	if (!file_name)
		return (close_heredoc_fds(setup), 1);	// >>> check later on to fix
	setup->heredoc->fd[i] = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (setup->heredoc->fd[i] == -1)
		return (close_heredoc_fds(setup), free(file_name), 1);
	get_delimiter(setup, red);
	loding_heredoc(setup);
	if (refresh_fds(setup, file_name) == 1)	// >>> refresh the offset of the fd
		return (close_heredoc_fds(setup), free(file_name), 1);
	free(file_name);
	return (0);
}

void	init_heredoc(t_setup *setup, t_tree *tree)
{
	t_redirections *redir;

	redir = NULL;
	if (!tree)
        return ;
    if (tree->cmd && tree->cmd->redirections)
    {
        redir = tree->cmd->redirections;
        while (redir)
        {
            if (redir->type == TOKEN_HERDOC)
			{
                if (get_heredoc_fds(setup, redir) == 1)
				{
					ft_perror(setup, "heredoc process failed\n", EXIT_FAILURE);
					break;
				}
				setup->i++;		// >>> index of the array of fds
			}
			redir = redir->next;
		}
	}
	init_heredoc(setup, tree->left);
	init_heredoc(setup, tree->right);
}

void	heredoc_process(t_setup *setup, t_tree *tree)
{
	setup->i = 0;
	init_heredoc(setup, tree);
}
