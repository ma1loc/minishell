/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_is_split2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytabia <ytabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:06:41 by ytabia            #+#    #+#             */
/*   Updated: 2025/04/22 19:06:42 by ytabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_shell.h"

int	skip_whitespace(char *input, int i)
{
	while (input[i] != '\0' && (input[i] == ' ' || input[i] == '\t'))
		i++;
	return (i);
}

int	get_quotes_type(t_token *token)
{
	if (token->quotes_info)
		return (token->quotes_info->quotes_type);
	return (0);
}

t_token	*set_last_inserted(t_token *prev)
{
	if (prev == NULL)
		return (NULL);
	else
		return (prev);
}

int	extract_word(char *input, int i, char *buff)
{
	int	j;

	j = 0;
	while (input[i] != '\0' && input[i] != ' ' && input[i] != '\t')
		buff[j++] = input[i++];
	buff[j] = '\0';
	return (i);
}

void handel_is_split(t_token *tokens, t_token **head)
{
    t_token *current;
    t_token *prev;

    current = tokens;
    prev = NULL;
    while (current)
    {
        if (current->type == TOKEN_HERDOC)
        {
            prev = current;
            current = current->next->next;
            continue;
        }
        if (current->is_split == 1 && current->value)
            current = handle_split_token(current, prev, head);
        else
        {
            prev = current;
            current = current->next;
        }
    }
}
