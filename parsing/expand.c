/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytabia <ytabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:10:31 by ytabia            #+#    #+#             */
/*   Updated: 2025/04/23 14:15:34 by ytabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../srcs/mini_shell.h"
// #include "tokenizer.h"
# include "mini_shell.h"


void	expand_env_vars(t_token *tokens, t_setup *setup)
{
	t_token	*current;
	char	*expanded;

	current = tokens;
	setup->token = current;
	while (current)
	{
		if (current->type == TOKEN_HERDOC)
		{
			current = current->next->next;
			continue ;
		}
		expanded = expand_env_in_string(current->value, setup);
		if (expanded != NULL)
		{
			gc_free(g_gc, current->value);
			current->value = expanded;
		}
		current = current->next;
		setup->token = current;
	}
}

char	*expand_env_in_string(char *str, t_setup *setup)
{
	char			*rslt;
	t_expand_data	data;
	t_token			*token;
	int				res;

	token = setup->token;
	if (!str || !token || !token->quotes_info)
		return (NULL);
	data.ptr = str;
	data.buff_index = 0;
	while (*data.ptr)
	{
		res = handle_dollar_expansion(&data, setup);
		if (res == -1)
			return (NULL);
		if (res == 1)
			continue ;
		if (res == 2)
			break ;
		data.buff[data.buff_index++] = *data.ptr;
		data.ptr++;
	}
	data.buff[data.buff_index] = '\0';
	rslt = ft_strdup(data.buff);
	return (rslt);
}

int	handle_dollar_expansion(t_expand_data *data, t_setup *setup)
{
	t_token	*token;

	token = setup->token;
	if (*data->ptr == '$' && (token->quotes_info->quotes_type == 0
			|| token->quotes_info->quotes_type == 2))
	{
		if (*(data->ptr + 1) == '?')
		{
			if (expand_exit_status(data, setup))
				return (-1);
			return (1);
		}
		if (*(data->ptr + 1) == '\0')
		{
			data->buff[data->buff_index++] = *data->ptr;
			return (2);
		}
		data->ptr++;
		data->ptr = extract_var_name(data);
		data->env_value = get_env_value(data->var_name, setup);
		copy_env_value_if_valid(data, token);
		return (1);
	}
	return (0);
}


int	expand_exit_status(t_expand_data *data, t_setup *setup)
{
	char	*exit;

	exit = ft_itoa_(setup->exit_stat);
	if (!exit)
		return (1);
	ft_strcpy(data->buff + data->buff_index, exit);
	data->buff_index += ft_strlen(exit);
	data->ptr += 2;
	gc_free(g_gc, exit);
	return (0);
}

char	*extract_var_name(t_expand_data *data)
{
	char	*start;

	start = data->ptr;
	data->var_index = 0;
	while (*start && *start != '$' && (isalnum(*start) || *start == '_'))
		data->var_name[data->var_index++] = *start++;
	data->var_name[data->var_index] = '\0';
	return (start);
}
