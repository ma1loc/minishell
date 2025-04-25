/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokinizer2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytabia <ytabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:29:31 by ytabia            #+#    #+#             */
/*   Updated: 2025/04/25 12:28:47 by ytabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_token	*add_token(t_token **head, char *value, t_token_type type,
		int quotes_type)
{
	t_token	*new_token;
	t_token	*current;

	new_token = gc_malloc(g_gc, sizeof(t_token));
	if (!new_token)
		return (NULL);
	ft_memset(new_token, 0, sizeof(t_token));
	new_token->value = ft_strdup(value);
	new_token->type = type;
	new_token->quotes_info = gc_malloc(g_gc, sizeof(t_quotes_info));
	if (!new_token->quotes_info)
		return (gc_free(g_gc, new_token->value), gc_free(g_gc, new_token),
			NULL);
	new_token->quotes_info->quotes_type = quotes_type;
	if (*head == NULL)
	{
		*head = new_token;
		return (new_token);
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_token;
	return (new_token);
}

void	process_quote_char(t_process_data *data, t_quotes_info *info)
{
	static int	in_dquote;
	static int	in_squote;

	if (data->str[data->i] == '"' && in_squote == 0)
	{
		in_dquote = !in_dquote;
		if (in_dquote)
			info->quotes_type = 2;
	}
	else if (data->str[data->i] == '\'' && in_dquote == 0)
	{
		in_squote = !in_squote;
		if (in_squote)
			info->quotes_type = 1;
	}
	else
		data->result[(data->j)++] = data->str[data->i];
	(data->i)++;
}

t_quotes_info	check_just_quotes(t_process_data *data, t_quotes_info info,
		int len)
{
	if (data->j == 0 && len > 0)
		return (info);
	return (info);
}

t_quotes_info	check_empty_string(t_process_data *data, t_quotes_info info,
		int len)
{
	if (data->j == 0 && len == 0)
	{
		gc_free(g_gc, data->result);
		info.stripped_text = NULL;
	}
	return (info);
}

t_quotes_info	strip_quotes(char *str)
{
	t_quotes_info	info;
	t_process_data	data;
	int				len;

	info.quotes_type = 0;
	len = ft_strlen(str);
	data.result = gc_malloc(g_gc, len + 1);
	if (!data.result)
	{
		info.stripped_text = NULL;
		return (info);
	}
	data.str = str;
	data.i = 0;
	data.j = 0;
	while (data.i < len)
		process_quote_char(&data, &info);
	data.result[data.j] = '\0';
	info.stripped_text = data.result;
	check_just_quotes(&data, info, len);
	info = check_empty_string(&data, info, len);
	return (info);
}
