/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_is_split1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytabia <ytabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:06:16 by ytabia            #+#    #+#             */
/*   Updated: 2025/04/24 20:04:18 by ytabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_token	*setup_token(char *value, int token_type, int quotes_type)
{
	t_token	*new_token;

	new_token = gc_malloc(g_gc, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(value);
	new_token->type = token_type;
	new_token->is_space = 0;
	new_token->is_split = 0;
	new_token->quotes_info = gc_malloc(g_gc, sizeof(t_quotes_info));
	if (!new_token->quotes_info)
		return (gc_free(g_gc, new_token->value), gc_free(g_gc, new_token),
			NULL);
	new_token->quotes_info->quotes_type = quotes_type;
	new_token->next = NULL;
	return (new_token);
}

t_token	*insert_new_token(t_insert_info info, t_token *last_inserted)
{
	t_token	*new_token;

	new_token = setup_token(info.value, info.token_type, info.quotes_type);
	if (!new_token)
		return (NULL);
	if (last_inserted == NULL)
	{
		if (*(info.head) == NULL)
			*(info.head) = new_token;
		else
		{
			new_token->next = (*(info.head))->next;
			(*(info.head))->next = new_token;
		}
	}
	else
	{
		new_token->next = last_inserted->next;
		last_inserted->next = new_token;
	}
	return (new_token);
}

t_token	*process_word(t_insert_info info, char *buff, t_token *last_inserted)
{
	info.value = buff;
	return (insert_new_token(info, last_inserted));
}

t_token	*process_split_token(char *input, t_token **head,
		t_token *last_inserted, int quotes_type)
{
	int				i;
	char			buff[1024];
	t_insert_info	info;

	i = 0;
	info.head = head;
	info.token_type = TOKEN_WORD;
	info.quotes_type = quotes_type;
	while (input[i] != '\0')
	{
		if (input[i] == ' ' || input[i] == '\t')
			i = skip_whitespace(input, i);
		else
		{
			i = extract_word(input, i, buff);
			if (buff[0] != '\0')
				last_inserted = process_word(info, buff, last_inserted);
		}
	}
	return (last_inserted);
}

t_token	*handle_split_token(t_token *current, t_token *prev, t_token **head)
{
	t_token	*last_inserted;
	t_token	*next;

	last_inserted = set_last_inserted(prev);
	last_inserted = process_split_token(current->value, head, last_inserted,
			get_quotes_type(current));
	next = current->next;
	remove_token(head, current);
	return (next);
}
