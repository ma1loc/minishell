# include "mini_shell.h"

// int		should_expand(t_setup *setup)
// {
// 	static t_token	*token;
// 	int 	quotes;

// 	token = setup->token->next;
// 	quotes = token->quotes_info->quotes_type;
// 	printf("if token -> %s\n", token->value);
// 	if (quotes == 0 && token->type == TOKEN_WORD)
// 		return (1);
// 	else
// 	{
// 		token = token->next;
// 		quotes = token->quotes_info->quotes_type;
// 		printf("else token -> %s\n", token->value);
// 		if (quotes == 0 && token->type == TOKEN_WORD)
// 			return (1);
// 		return (0);
// 	}
// 	return (0);

// 	// token = setup->token;
// 	// while (token)
// 	// {
// 	// 	if (token->type == TOKEN_HERDOC)
// 	// 	{

// 	// 	}
// 	// 	token = token->next
// 	// }
// }

// int		should_expand(t_setup *setup)
// {
// 	t_token	*token;
// 	int 	quotes;
	
// 	token = setup->token->next;
// 	quotes = token->quotes_info->quotes_type;
// 	printf("token -> %s\n", token->next->value);
// 	if (quotes == 0)
// 		return (1);
// 	return (0);
// }

void	cleanup_heredoc(t_setup *setup)
{
	int i;

	i = 0;
	if (setup->heredoc->fd[i])
	{
		while (setup->heredoc->fd[i])
		{
			close(setup->heredoc->fd[i]);
			i++;
		}
	}
	i = 0;
	if (setup->heredoc->file_name[i])
	{
		while (setup->heredoc->file_name[i])
		{
			unlink(setup->heredoc->file_name[i]);
			gc_free(g_gc, setup->heredoc->file_name[i]);
			i++;
		}
	}
}

char	*get_file_name(t_setup *setup)
{
	char	*file_num;
	char	*file_name;

	file_num = ft_itoa(setup->i);
	if (!file_num)
		allocation_failed_msg();
	file_name = ft_strjoin("/tmp/heredoc", file_num);
	if (!file_name)
		allocation_failed_msg();
	gc_free(g_gc, file_num);
	return (file_name);
}

int	refresh_fds(t_setup *setup, char *file_name)
{
	int i;

	i = setup->i;
	close(setup->heredoc->fd[i]);
	setup->heredoc->fd[i] = open(file_name, O_RDONLY, 0644);
	if (!setup->heredoc->fd[i])
	{
		ft_perror(setup, NULL, EXIT_FAILURE);
		return (cleanup_heredoc(setup), free(file_name),1);
	}
	return (0);
}

int is_heredoc_in_pipe(t_tree *tree)
{
    if (tree->left && is_heredoc(tree->left))
        return (1);
    if (tree->right && is_heredoc(tree->right))
        return (1);
    return (0);
}

int is_heredoc(t_tree *tree)
{
    t_redirections *redir;

    if (!tree)
	return (0);
	
    if (tree->cmd && tree->cmd->redirections)
    {
		redir = tree->cmd->redirections;
        while (redir)
        {
            if (redir->type == TOKEN_HERDOC)
                return (1);
            redir = redir->next;
        }
    }
	if (is_heredoc_in_pipe(tree))
		return (1);
    return (0);
}
