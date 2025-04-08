# include "mini_shell.h"

// tests
// $HOME '$HOME' "$HOME"
// }: bad substitution

void	loding_heredoc(t_setup *setup, t_gc *gc)
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
		if (should_expand(setup))
			parsing_heredoc_input(setup, input, gc);
		else
		{
			write(setup->heredoc->fd[setup->i], input, ft_strlen(input));
			write(setup->heredoc->fd[setup->i], "\n", 1);
		}
		free(input);
	}
}

void	get_delimiter(t_setup *setup, t_redirections *red, t_gc *gc)
{
	if (setup->heredoc->delimiter)
		gc_free(gc, setup->heredoc->delimiter);

	setup->heredoc->delimiter = ft_strdup(red->file_name, gc);
	red = red->next;
	return ;
}

int	get_heredoc_fds(t_setup *setup, t_redirections *red, t_gc *gc)
{
	char	*file_name;
	int		i;

	i = setup->i;
	file_name = get_file_name(setup, gc);
	if (!file_name)
	return (cleanup_heredoc(setup, gc), 1);
	setup->heredoc->file_name[setup->i] = ft_strdup(file_name, gc);
	if (!setup->heredoc->file_name[setup->i])
		allocation_failed_msg(gc);
	setup->heredoc->fd[i] = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (setup->heredoc->fd[i] < 0)
		return (cleanup_heredoc(setup, gc), 1);
	get_delimiter(setup, red, gc);
	loding_heredoc(setup, gc);
	if (refresh_fds(setup, file_name, gc) == 1)		// >>> refresh the offset of the fd
		return (cleanup_heredoc(setup, gc), 1);
	gc_free(gc, file_name);
	return (0);
}

void	init_heredoc(t_setup *setup, t_tree *tree, t_gc *gc)
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
				setup->heredoc_flag = 1;
                if (get_heredoc_fds(setup, redir, gc) == 1)
				{
					ft_perror(setup, "heredoc process failed\n", EXIT_FAILURE);
					break;
				}
				setup->i++;		// >>> index of the array of fds
			}
			redir = redir->next;
		}
	}
	init_heredoc(setup, tree->left, gc);
	init_heredoc(setup, tree->right, gc);
}

void	heredoc_process(t_setup *setup, t_tree *tree, t_gc *gc)
{
	// >>> to remove later on
	setup->heredoc->deleimiter_flag[0] = 1;


	setup->heredoc_flag = 0;
	setup->i = 0;
	init_heredoc(setup, tree, gc);
	setup->i = 0;	// >>> restor it to defule to use it again in the execution
}
