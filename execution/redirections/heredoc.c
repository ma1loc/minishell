# include "mini_shell.h"

// int		should_expand(t_token *token)
// {
// 	// t_token	*token;
// 	int 	quotes;
	
// 	// token = setup->token->next;
// 	while (token)
// 	{
// 		if (token->type == TOKEN_HERDOC)
// 		{
// 			token = token->next;
// 			break;
// 		}
// 		token = token->next;
// 	}
// 	quotes = token->quotes_info->quotes_type;
// 	printf("token -> %s\n", token->next->value);
// 	if (quotes == 0)
// 		return (1);
// 	return (0);
// }

// int		should_expand(t_setup *setup)
// {
// 	t_token	*token;
// 	int 	quotes;
	
// 	token = setup->token->next;
// 	quotes = token->quotes_info->quotes_type;
// 	printf("token to check it's qoutes -> %s\n", token->next->value);
// 	if (quotes == 0)
// 		return (1);
// 	return (0);
// }

void	loding_heredoc(t_setup *setup)
{
	char			*input;

	while (true)
	{
		input = readline("heredoc> ");
        if (input == NULL)
			do_eof_heredoc(setup);
        if (ft_strcmp(input, setup->heredoc->delimiter) == 0)
        {
            free(input);
            break;
        }
		if (input[0] == '\0')
            continue ;
		if (setup->heredoc->qoutes_type == 0)
			expand_heredoc_input(setup, input);
		else
		{
			write(setup->heredoc->fd[setup->i], input, ft_strlen(input));
			write(setup->heredoc->fd[setup->i], "\n", 1);
		}
		free(input);
	}
}

void	get_delimiter(t_setup *setup, t_redirections *red)
{
	if (setup->heredoc->delimiter)
		gc_free(g_gc, setup->heredoc->delimiter);

	setup->heredoc->delimiter = ft_strdup(red->file_name);
	red = red->next;
	return ;
}

void	get_delimiter_qoutes(t_setup *setup)
{
	setup->heredoc->qoutes_type = 0;

	while (setup->token)
	{
		if (setup->token->type == TOKEN_HERDOC)
		{
			setup->token = setup->token->next;
			// printf("current token -> %s\n", setup->token->value);
			setup->heredoc->qoutes_type = setup->token->quotes_info->quotes_type;
			break;
		}
		// printf("the token -> %s\n", setup->token->value);
		setup->token = setup->token->next;
		// break;
	}
	// setup->token = setup->token->next;
	// setup->token = setup->token->next;
	// setup->token = setup->token->next;
	// printf("token after -> %s\n", setup->token->value);
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
	// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	get_delimiter(setup, red);
	get_delimiter_qoutes(setup);
	// printf("token qoutes -> %d\n", setup->heredoc->qoutes_type);
	// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	loding_heredoc(setup);
	if (refresh_fds(setup, file_name) == 1)
		return (cleanup_heredoc(setup), 1);
	gc_free(g_gc, file_name);
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
					// i have to put it as a seprited msg
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



void heredoc_process(t_setup *setup, t_tree *tree)
{
    pid_t	pid;
    int		status;
	int		exit_status;

    pid = set_fork(setup);    
    if (pid == 0)
    {
		signal(SIGINT, heredoc_sigint);
		setup->i = 0;
		// >>>>>>>>>>>>>>>>>>>>>>>>>
        init_heredoc(setup, tree);
		// >>>>>>>>>>>>>>>>>>>>>>>>>
        setup->i = 0;
        execution(tree, setup);
		exit_status = setup->exit_stat;
		gc_destroy(g_gc);
		exit(exit_status);
    }
    waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		setup->exit_stat = WEXITSTATUS(status);
	signal(SIGINT, main_sigint);
	return ;
}
