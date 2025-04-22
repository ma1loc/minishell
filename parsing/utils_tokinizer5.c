/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokinizer5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytabia <ytabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:30:01 by ytabia            #+#    #+#             */
/*   Updated: 2025/04/22 19:30:02 by ytabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "../srcs/mini_shell.h"

int	handle_dollar_dquotes(char *input, t_tokinizer_state *state, t_quotes_info info, t_token **tokens)
{
	t_content_info	c_info;

	if (input[state->i + 1] == '"')
	{
		info.quotes_type = 2;
		c_info.input = input;
		c_info.start = state->i + 2;
		c_info.end = c_info.start;
		while (input[c_info.end] && input[c_info.end] != '"')
			c_info.end++;
		if (input[c_info.end] == '"')
		{
			c_info.length = c_info.end - c_info.start;
			c_info.content = malloc(c_info.length + 1);
			if (c_info.content)
			{
				return (process_token_content(&c_info, tokens, info, state));
			}
		}
	}
	return (0);
}

int	handle_dollar_squotes(char *input, t_tokinizer_state *state, t_quotes_info info, t_token **tokens)
{
	t_content_info	c_info;

	if (input[state->i + 1] == '\'')
	{
		info.quotes_type = 1;
		c_info.input = input;
		c_info.start = state->i + 2;
		c_info.end = c_info.start;
		while (input[c_info.end] && input[c_info.end] != '\'')
			c_info.end++;
		if (input[c_info.end] == '\'')
		{
			c_info.length = c_info.end - c_info.start;
			c_info.content = malloc(c_info.length + 1);
			if (c_info.content)
			{
				return (process_token_content(&c_info, tokens, info, state));
			}
		}
	}
	return (0);
}

int process_token_content(t_content_info *c_info, t_token **tokens, t_quotes_info info,t_tokinizer_state *state)
{
  t_token *new_token;
  
  strncpy(c_info->content, c_info->input + c_info->start, c_info->length);
  c_info->content[c_info->length] = '\0';
  new_token = add_token(tokens, c_info->content, TOKEN_WORD, info.quotes_type);
  if (c_info->input[c_info->end + 1] == ' ' || c_info->input[c_info->end + 1] == '\t')
  new_token->is_space = 1;
  else
  new_token->is_space = -1;
  free(c_info->content);
  state->i = c_info->end + 1;
  return (1);
}

int handle_dollar_quotes(char *input, t_tokinizer_state *state, t_token **tokens, t_quotes_info *info)
{
    if (handle_dollar_dquotes(input, state, *info, tokens))
        return (1);
    if (handle_dollar_squotes(input, state, *info, tokens))
        return (1);
    return (0);
}
