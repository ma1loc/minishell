/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokinizer4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytabia <ytabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:29:48 by ytabia            #+#    #+#             */
/*   Updated: 2025/04/22 19:29:49 by ytabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "../srcs/mini_shell.h"

void handle_double_operator(char *input, t_tokinizer_state *state, t_token **tokens, t_quotes_info info)
{
    if (input[state->i] == '>' && input[state->i + 1] == '>')
    {
        add_token(tokens, ">>", TOKEN_APPEND, info.quotes_type);
        state->i += 2;
    }
    else if (input[state->i] == '<' && input[state->i + 1] == '<')
    {
        add_token(tokens, "<<", TOKEN_HERDOC, info.quotes_type);
        state->i += 2;
    }
    else if (input[state->i] == '<' && input[state->i + 1] == '>')
    {
        add_token(tokens, "<>", TOKEN_RED_INOUT, info.quotes_type);
        state->i += 2;
    }
}

void handle_single_operator(char *input, t_tokinizer_state *state, t_token **tokens, t_quotes_info info)
{
    if (input[state->i] == '|')
    {
        add_token(tokens, "|", TOKEN_PIPE, info.quotes_type);
        state->i++;
    }
    else if (input[state->i] == '>')
    {
        add_token(tokens, ">", TOKEN_RED_OUT, info.quotes_type);
        state->i++;
    }
    else if (input[state->i] == '<')
    {
        add_token(tokens, "<", TOKEN_RED_IN, info.quotes_type);
        state->i++;
    }
}
void process_operators(char *input, t_tokinizer_state *state, t_token **tokens)
{
    t_quotes_info info;

    info.quotes_type = 0;
    handle_double_operator(input, state, tokens, info);
    handle_single_operator(input, state, tokens, info);
}

void process_normal_word(char *input, t_tokinizer_state *state)
{
  state->buff[state->j++] = input[state->i++];
}
