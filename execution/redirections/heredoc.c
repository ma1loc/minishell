# include "mini_shell.h"

void	loding_heredoc(t_setup *setup)
{
	char	*input;

	while (true)
	{
		input = readline("heredoc> ");
		if (input == NULL || ft_strcmp(input, setup->heredoc->delimiter) == 0)
			break;
		if (input[0] == '\0')
            continue ;
		if (!setup->token || ft_strlen(setup->token->value) == 0)
			continue ;
		if (should_expand(setup))
			expand_heredoc_input(setup, input);
		else
		{
			write(setup->heredoc->fd[setup->i], input, ft_strlen(input));
			write(setup->heredoc->fd[setup->i], "\n", 1);
		}
		free(input);
	}
	free(input);
}

void	get_delimiter(t_setup *setup, t_redirections *red)
{

	if (setup->heredoc->delimiter)
		gc_free(gc, setup->heredoc->delimiter);

	setup->heredoc->delimiter = ft_strdup(red->file_name);
	red = red->next;
	return ;
}

int	get_heredoc_fds(t_setup *setup, t_redirections *red)
{
	t_heredoc	*heredoc;
	char		*file_name;
	int			i;
	
	i = setup->i;
	heredoc = setup->heredoc;
	file_name = get_file_name(setup);
	heredoc->file_name[setup->i] = ft_strdup(file_name);
	if (!heredoc->file_name[setup->i])
		allocation_failed_msg();
	heredoc->fd[i] = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (heredoc->fd[i] < 0)
		return (cleanup_heredoc(setup), 1);
	get_delimiter(setup, red);
	loding_heredoc(setup);
	if (refresh_fds(setup, file_name) == 1)
		return (cleanup_heredoc(setup), 1);
	gc_free(gc, file_name);
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
				setup->heredoc_flag = 1;
                if (get_heredoc_fds(setup, redir) == 1)
				{
					ft_perror(setup, "heredoc process failed\n", EXIT_FAILURE);
					break;
				}
				setup->i++;
			}
			redir = redir->next;
		}
	}
	init_heredoc(setup, tree->left);
	init_heredoc(setup, tree->right);
}

void	heredoc_process(t_setup *setup, t_tree *tree)
{
	setup->heredoc_flag = 0;
	setup->i = 0;
	init_heredoc(setup, tree);
	setup->i = 0;	// >>> restor it to defult to use it again in the execution
}
