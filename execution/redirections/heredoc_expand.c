# include "mini_shell.h"

char	*get_env_val(t_setup *setup, char *key)
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

void	set_exit_status(t_setup *setup, char **result)
{
	char	*value;

	value = ft_itoa(setup->exit_stat);
	if (!value)
		allocation_failed_msg();
	*result = ft_strjoin(*result, value);
	gc_free(gc, value);
}

void	set_dollar_sign(t_setup *setup, char **result)
{
	char *value;

	value = ft_itoa(setup->exit_stat);
	if (!value)
		allocation_failed_msg();
	*result = ft_strjoin(*result, value);
	gc_free(gc, value);
}

void	expand_env_variable(t_setup *setup, char *input, int *i, char **result)
{
	int		start;
	char	*key;
	char	*value;

	start = ++(*i);
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	key = ft_substr(input, start, *i - start);
	value = get_env_val(setup, key);
	if (value)
		*result = ft_strjoin(*result, value);
	gc_free(gc, key);
}

void	expand_heredoc_input(t_setup *setup, char *input)
{
	int		i;
	char	*result;
	
	i = 0;
	result = NULL;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] == '?')
		{
			i += 2;
			set_dollar_sign(setup, &result);
			continue;
		}
		else if (input[i] == '$' && input[i + 1] &&
			(ft_isalpha(input[i + 1]) || input[i + 1] == '_'))
		{
			expand_env_variable(setup, input, &i, &result);
			continue;
		}
		result = ft_strjoin(result, char_to_str(input[i]));
		i++;
	}
	write(setup->heredoc->fd[setup->i], result, ft_strlen(result));
	write(setup->heredoc->fd[setup->i], "\n", 1);
	gc_free(gc, result);
}
