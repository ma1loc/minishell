# include "mini_shell.h"

// tests
// $HOME '$HOME' "$HOME"
// }: bad substitution

char *char_to_str(char c)
{
	char	*str;

    str = malloc(2);
    if (!str)
        return (NULL);
    str[0] = c;
    str[1] = '\0';
    return (str);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char *new;
	
	new = ft_strjoin(s1, s2);
	if (!new)
		return (NULL);
	free(s1);
	return (new);
}

int		should_expand(t_setup *setup)
{
	int i;

	i = setup->i;
	if (setup->heredoc->deleimiter_flag[i] == 1)
		return (1); //	>>> expand
	return (0); //		>>> not expand
}

char	*get_env_val(t_setup *setup, char *key)	// >>> value
{
	t_env *env;

	env = NULL;
	if (!is_valid_identifier(key))
		return (NULL);
	env = setup->env;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	parsing_heredoc_input(t_setup *setup, char *input)
{
	// if the delimiter have qutes no expand
	// parsing the qutes
	// delemiter most check if there's qutes other wayse if it single or double just print it with it's qutes
	// update input with it's env value
	int		i;
	int		start;
	char	*key;
	char	*value;
	char	*result;
	char	*_char;
	
	// >>> here i have to get the env key
	// >>> but first thing i have to check it if valid or not, i mean the fist char
	// >>> i have to split it
	// >>> $->$		$$(skipe)	$$$->$
	i = 0;
	result = ft_strdup("");
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] &&
			(ft_isalpha(input[i + 1]) || input[i + 1] == '_'))
		{
			start = ++i;
			while (ft_isalnum(input[i]) || input[i] == '_')
				i++;
			key = ft_substr(input, start, i - start);
			value = get_env_val(setup, key);
			if (value)
				result = ft_strjoin_free(result, value);
			free(key);
		}
		else
		{
			_char = char_to_str(input[i]);
			result = ft_strjoin_free(result, _char);
			i++;
		}
	}
	write(setup->heredoc->fd[setup->i], result, ft_strlen(result));
	write(setup->heredoc->fd[setup->i], "\n", 1);
	free(result);
}


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
		if (should_expand(setup))
			parsing_heredoc_input(setup, input);
		else
		{
			write(setup->heredoc->fd[setup->i], input, ft_strlen(input));
			write(setup->heredoc->fd[setup->i], "\n", 1);
		}
		free(input);
	}
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

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
	if (!file_name)
	return (cleanup_heredoc(setup), 1);
	setup->heredoc->file_name[setup->i] = ft_strdup(file_name);
	setup->heredoc->fd[i] = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (setup->heredoc->fd[i] < 0)
		return (cleanup_heredoc(setup), free(file_name), 1);
	get_delimiter(setup, red);
	loding_heredoc(setup);
	if (refresh_fds(setup, file_name) == 1)		// >>> refresh the offset of the fd
		return (cleanup_heredoc(setup), free(file_name), 1);
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
				setup->heredoc_flag = 1;
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
	// >>> to remove later on
	setup->heredoc->deleimiter_flag[0] = 1;


	setup->heredoc_flag = 0;
	setup->i = 0;
	init_heredoc(setup, tree);
	setup->i = 0;	// >>> restor it to defule to use it again in the execution
}
