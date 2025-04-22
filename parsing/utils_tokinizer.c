/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokinizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytabia <ytabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:19:11 by ytabia            #+#    #+#             */
/*   Updated: 2025/04/22 19:19:12 by ytabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/mini_shell.h"
#include "tokenizer.h"

void	process_spaces(t_tokinizer_state *state, t_token **tokens)
{
	t_quotes_info	info;

	if (state->j > 0)
	{
		state->buff[state->j] = '\0';
		info = strip_quotes(state->buff);
		if (info.stripped_text != NULL)
		{
			add_token(tokens, info.stripped_text, TOKEN_WORD, info.quotes_type);
			free(info.stripped_text);
		}
		state->j = 0;
	}
	state->i++;
}

void	process_special_tokens(char *input, t_tokinizer_state *state,
		t_token **tokens)
{
	t_quotes_info	info;

	if (state->j > 0)
	{
		state->buff[state->j] = '\0'; // save any buffered word first
		info = strip_quotes(state->buff);
		if (info.stripped_text != NULL)
		{
			add_token(tokens, info.stripped_text, TOKEN_WORD, info.quotes_type);
			free(info.stripped_text);
		}
		state->j = 0;
	}
	process_operators(input, state, tokens);
}

void	process_remainder_text(t_tokinizer_state *state, t_token **tokens)
{
	t_quotes_info	info;

	if (state->j > 0)
	{
		state->buff[state->j] = '\0';
		info = strip_quotes(state->buff);
		if (info.stripped_text != NULL)
		{
			add_token(tokens, info.stripped_text, TOKEN_WORD, info.quotes_type);
			free(info.stripped_text);
		}
		state->j = 0;
	}
}

void	process_dollar(char *input, t_tokinizer_state *state, t_token **tokens)
{
	t_quotes_info	info;
	t_token			*new_token;
	int				is_space;

	ft_memset(&info, 0, sizeof(t_quotes_info));
	is_space = -1;
	if (handle_dollar_quotes(input, state, tokens, &info))
		return ;
	state->buff[state->j++] = input[state->i++];
	if (input[state->i] == '?')
		state->buff[state->j++] = input[state->i++];
	while (input[state->i] != '\0' && (isalnum(input[state->i])
			|| input[state->i] == '_'))
		state->buff[state->j++] = input[state->i++];
	if (input[state->i] == ' ' || input[state->i] == '\t')
		is_space = 1;
	state->buff[state->j] = '\0';
	info = strip_quotes(state->buff);
	if (info.stripped_text != NULL)
	{
		new_token = add_token(tokens, info.stripped_text, TOKEN_WORD,
				info.quotes_type);
		new_token->is_space = is_space;
		free(info.stripped_text);
	}
	state->j = 0;
}

void	process_quotes(char *input, t_tokinizer_state *state, t_token **tokens)
{
	char			quote_char;
	t_quotes_info	info;
	t_token			*new_token;
	int				is_space;

	is_space = -1;
	quote_char = input[state->i];
	state->buff[state->j++] = input[state->i++];
	while (input[state->i] != '\0' && input[state->i] != quote_char)
	{
		state->buff[state->j++] = input[state->i++];
	}
	state->buff[state->j++] = input[state->i++];
	if (input[state->i] == ' ')
		is_space = 1;
	state->buff[state->j] = '\0';
	info = strip_quotes(state->buff);
	if (info.stripped_text != NULL)
	{
		new_token = add_token(tokens, info.stripped_text, TOKEN_WORD,
				info.quotes_type);
		new_token->is_space = is_space;
		free(info.stripped_text);
	}
	state->j = 0;
}
