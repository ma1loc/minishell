# include "mini_shell.h"

void	close_fds(t_setup *setup)
{
	int i;
	int	count;

	i = 0;
	count = setup->heredoc->count;
	while (i <= count)
	{
		close(setup->heredoc->fd[i]);
		i++;
	}
}

char	*get_file_name(t_setup *setup)
{
	char	*file_num;
	char	*file_name;

	file_num = ft_itoa(setup->heredoc->count);
	if (!file_num)
		return (NULL);
	file_name = ft_strjoin("/tmp/heredoc", file_num);
	if (!file_name)
	{
		free(file_num);
		return (NULL);
	}
	free(file_num);
	return (file_name);
}

// >>> refresh the offset of the fd
int	refresh_fds(t_setup *setup, char *file_name)
{
	int	count;

	count = setup->heredoc->count;
	close(setup->heredoc->fd[count]);
	setup->heredoc->fd[count] = open(file_name, O_RDONLY, 0644);
	if (!setup->heredoc->fd[count])
		return (close_fds(setup),free(file_name), 1);
	free(file_name);
	return (0);
}

int	get_heredoc_fds(t_tree *tree, t_setup *setup)
{
	char	*file_name;
	int		count;
	char	*input;
	
	count = setup->heredoc->count;
	file_name = get_file_name(setup);
	if (!file_name)
		return (close_fds(setup), 1);	// >>> check litter on

	setup->heredoc->fd[count] = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (setup->heredoc->fd[count] == -1)
		return (close_fds(setup), free(file_name), 1);

	while (true)
	{
		input = readline("heredoc> ");
		if (input == NULL || ft_strcmp(input, tree->cmd->redirections->file_name) == 0)
		{
			free(input);
			break;
		}
		write(setup->heredoc->fd[setup->i], input, ft_strlen(input));
		write(setup->heredoc->fd[setup->i], "\n", 1);
		free(input);
	}
	// >>> refresh the offset of the fd
	if (refresh_fds(setup, file_name) == 1)
		return (1);
	return (0);
}

void	get_heredoc_count(t_tree *tree, t_setup *setup)
{
	if (!tree)
        return ;

    if (tree->cmd && tree->cmd->redirections)
    {
        t_redirections *redir = tree->cmd->redirections;
        while (redir)
        {
            if (redir->type == TOKEN_HERDOC)
			{
                if (get_heredoc_fds(tree, setup) == 1)
				{
					ft_perror(setup, "heredoc process failed\n", 1);
					break;
				}
				setup->i++;
				setup->heredoc->count++;
			}
            redir = redir->next;
        }
    }
    get_heredoc_count(tree->left, setup);
    get_heredoc_count(tree->right, setup);
}

void	process_heredoc(t_tree *tree, t_setup *setup)
{
	setup->heredoc->count = 0;	// >>> count how many heredocs there
	get_heredoc_count(tree, setup);
}
