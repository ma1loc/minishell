# include "mini_shell.h"

void	loding_heredoc(t_setup *setup, t_tree *tree)
{
	(void)tree;
	char	*input;

	while (true)
	{
		input = readline("heredoc> ");
		if (input == NULL || ft_strcmp(input, setup->heredoc->delimiter) == 0)
		{
			free(input);
			break;
		}
		// setup->heredoc->fd[setup->i] => fd
		write(setup->heredoc->fd[setup->i], input, ft_strlen(input));
		write(setup->heredoc->fd[setup->i], "\n", 1);
		free(input);
	}
}

// char	*get_delimiter(t_redirections *redirection)
void	get_delimiter(t_setup *setup, t_redirections *redirection)
{

	if (setup->heredoc->delimiter)
		free(setup->heredoc->delimiter);

	setup->heredoc->delimiter = ft_strdup(redirection->file_name);
	// printf("delimiter -> %s\n", redirection->file_name);
	redirection = redirection->next;
	return ;
}

int	get_heredoc_fds(t_tree *tree, t_setup *setup, t_redirections *red)
{
	(void)red;
	char	*file_name;
	int		count;
	
	count = setup->heredoc->count;
	file_name = get_file_name(setup);
	if (!file_name)
		return (close_fds(setup), 1);	// >>> check later on
	setup->heredoc->fd[count] = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (setup->heredoc->fd[count] == -1)
		return (close_fds(setup), free(file_name), 1);
	// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	get_delimiter(setup, red);
	loding_heredoc(setup, tree);
	// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	// >>> refresh the offset of the fd
	if (refresh_fds(setup, file_name) == 1)
		return (1);
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
                if (get_heredoc_fds(tree, setup, redir) == 1)
				{
					ft_perror(setup, "heredoc process failed\n", EXIT_FAILURE);
					break;
				}
				setup->i++;
				setup->heredoc->count++;
			}
			redir = redir->next;
		}
	}
	init_heredoc(setup, tree->left);
	init_heredoc(setup, tree->right);
}

void	heredoc_process(t_setup *setup, t_tree *tree)
{
	setup->heredoc->count = 0;	// >>> count how many heredocs there
	init_heredoc(setup, tree);
}

