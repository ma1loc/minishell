/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytabia <ytabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:07:28 by ytabia            #+#    #+#             */
/*   Updated: 2025/04/24 20:06:11 by ytabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

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

	redir = gc_malloc(g_gc, sizeof(t_redirections));
	if (!redir)
		return (NULL);
	if (file_name != NULL)
		redir->file_name = ft_strdup(file_name);
	else
		redir->file_name = NULL;
	redir->type = type;
	redir->next = NULL;
	return (redir);
}

int	is_single_quote(char *value)
{
	return ((value[0] == '"' || value[0] == '\'') && (ft_strlen(value) == 1));
}

void	process_args(t_args_list *current, t_command *cmd, int *i)
{
	char	combined_args[1024];

	while (current != NULL)
	{
		if (is_single_quote(current->value) && current->next
			&& is_single_quote(current->next->value))
		{
			ft_strcpy(combined_args, current->value);
			ft_strcat(combined_args, current->next->value);
			cmd->args[(*i)++] = ft_strdup(combined_args);
			current = current->next->next;
		}
		else
		{
			cmd->args[(*i)++] = ft_strdup(current->value);
			current = current->next;
		}
	}
	cmd->args[*i] = NULL;
}
