# include "mini_shell.h"

int		should_expand(t_setup *setup)
{
	int i;

	i = setup->i;
	// if (setup->expand->quotes_type == 1)
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

	// if the delimiter have qutes no expand
	// parsing the qutes
	// delemiter most check if there's qutes other wayse if it single or double just print it with it's qutes
	// update input with it's env value
	// >>> here i have to get the env key
	// >>> but first thing i have to check it if valid or not, i mean the fist char
	// >>> i have to split it
	// >>> $->$		$$(skipe)	$$$->$
	// >>> qutes in heredoc "$HOME"
	// $HOME" '$HOME' '$HOME "$HOME $HOME' $HOME" "$HOME"

	// >>>> to check it <<<<
	// handel -> double $ signe
	// handel -> $?

void	parsing_heredoc_input(t_setup *setup, char *input)
{
	int		i;
	int		start;
	char	*result;
	char	*_char;
	char	*key;
	char	*value;
	
	i = 0;
	result = NULL;
	key = NULL;
	value = NULL;
	_char = NULL; 
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
