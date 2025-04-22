/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytabia <ytabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:45:47 by ytabia            #+#    #+#             */
/*   Updated: 2025/04/22 19:40:06 by ytabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/mini_shell.h"
#include "tokenizer.h"

int	check_pipes(char *input, int len, int *i)
{
	int			j;
	static int	in_quotes;

	j = 0;
	if (input[*i] == '"')
	{
		in_quotes = !in_quotes;
		return (0);
	}
	if (input[*i] == '|' && !in_quotes)
	{
		if (*i == 0)
			return (1);
		if (*i > 0 && input[*i - 1] == '|')
			return (1);
		j = *i + 1;
		while (j < len && (input[j] == ' ' || input[j] == '\t'))
			j++;
		if (j < len && input[j] == '|')
			return (1);
	}
	if (*i == len - 1 && input[*i] == '|' && !in_quotes)
		return (1);
	return (0);
}

int	check_redirections(char *input, int len, int *i)
{
	int	j;

	if (input[*i] == '<' || input[*i] == '>')
	{
		if (*i + 1 < len && input[*i] == input[*i + 1])
		{
			j = *i + 2;
			while (j < len && (input[j] == ' ' || input[j] == '\t'))
				j++;
			if (j >= len && input[j] == '\0')
				return (1);
		}
		else
		{
			j = *i + 1;
			while (j < len && (input[j] == ' ' || input[j] == '\t'))
				j++;
			if (j >= len || input[j] == '\0')
				return (1);
			if (input[j] == '|')
				return (1);
		}
	}
	return (0);
}

int	check_quotes_syntax(t_setup *setup)
{
    int     i;
    int     in_quotes;
    char    quoest_char;
    int     len;

    i = 0;
    in_quotes = 0;
    quoest_char = 0;
    len = strlen(setup->input);
    while (setup->input[i] != '\0')
    {
        i = skip_whitespace(setup->input, i);

        if (check_syntax(setup->input, len, &i) != 0)
        {
            in_quotes = 1;
            break;
        }

        check_unclosed_quotes(setup, &i, &in_quotes, &quoest_char);
        i++;
    }
    return (handle_syntax_error(setup, in_quotes));
}

void	tokenize_loop(char *input, t_tokinizer_state *state,t_token **tokens)
{
	while (input[state->i] != '\0')
	{
		if (input[state->i] == ' ' || input[state->i] == '\t')
			process_spaces(state, tokens);
		else if (input[state->i] == '|' || input[state->i] == '<'
			|| input[state->i] == '>')
			process_special_tokens(input, state, tokens);
		else if (input[state->i] == '$')
			process_dollar(input, state, tokens);
		else if (input[state->i] == '"' || input[state->i] == '\'')
			process_quotes(input, state, tokens);
		else
			process_normal_word(input, state);
	}
}

t_token	*tokenize(t_setup *setup)
{
	t_tokinizer_state	*state;
	t_token				*tokens;
	char				*input;

	input = setup->input;
	tokens = NULL;
	state = malloc(sizeof(t_tokinizer_state));
	if (!state)
		return (NULL);
	state->i = 0;
	state->j = 0;
	memset(state->buff, 0, sizeof(state->buff));
	if (!setup->input || check_quotes_syntax(setup) != 0)
		return (free(state), NULL);
	tokenize_loop(input, state, &tokens);
	process_remainder_text(state, &tokens);
	expand_env_vars(tokens, setup);
	handel_is_split(tokens, &tokens);
	return (free(state), tokens);
}
