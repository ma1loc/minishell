/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytabia <ytabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:07:28 by ytabia            #+#    #+#             */
/*   Updated: 2025/04/22 19:07:29 by ytabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/mini_shell.h"
#include "tokenizer.h"

void	add_redirection_to_list(t_command *cmd, char *file_name,
		t_token_type type)
{
	t_redirections	*current_redir;
	t_redirections	*new_redir;

	if (!cmd)
		return ;
	new_redir = new_redirection(file_name, type);
	if (!new_redir)
		return ;
	if (!cmd->redirections)
	{
		cmd->redirections = new_redir;
		return ;
	}
	current_redir = cmd->redirections;
	while (current_redir->next != NULL)
	{
		current_redir = current_redir->next;
	}
	current_redir->next = new_redir;
}

t_redirections	*new_redirection(char *file_name, t_token_type type)
{
	t_redirections	*redir;

	redir = malloc(sizeof(t_redirections));
	if (!redir)
		return (NULL);
	if (file_name != NULL)
		redir->file_name = strdup(file_name);
	else
		redir->file_name = NULL;
	redir->type = type;
	redir->next = NULL;
	return (redir);
}

int	is_single_quote(char *value)
{
	return (value[0] == '"' || value[0] == '\'') && (strlen(value) == 1);
}

void	process_args(t_args_list *current, t_command *cmd, int *i)
{
	char	combined_args[1024];

	while (current != NULL)
	{
		if (is_single_quote(current->value) && current->next
			&& is_single_quote(current->next->value))
		{
			strcpy(combined_args, current->value);
			strcat(combined_args, current->next->value);
			cmd->args[(*i)++] = strdup(combined_args);
			current = current->next->next;
		}
		else
		{
			cmd->args[(*i)++] = strdup(current->value);
			current = current->next;
		}
	}
	cmd->args[*i] = NULL;
}
