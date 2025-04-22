/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytabia <ytabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:09:59 by ytabia            #+#    #+#             */
/*   Updated: 2025/04/22 19:10:00 by ytabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/mini_shell.h"
#include "tokenizer.h"

t_command	*creat_new_node_command(t_command *commandes)
{
	commandes = malloc(sizeof(t_command)); // creat new commande
	if (!commandes)
		return (NULL);
	commandes->name = NULL;
	commandes->args = NULL;
	commandes->redirections = NULL;
	commandes->type = 0;
	commandes->next = NULL;
	return (commandes);
}
void		remove_token(t_token **head, t_token *current)
{
	t_token	*temp;
	t_token	*prev;

	if (head == NULL || *head == NULL || current == NULL)
		return ;
	if (*head == current)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp->value);
		if (temp->quotes_info)
			free(temp->quotes_info);
		free(temp);
		return ;
	}
	prev = *head;
	while (prev && prev->next != current)
		prev = prev->next;
	if (prev)
	{
		prev->next = current->next;
		free(current->value);
		free(current);
	}
}

int	join_tokens(t_token **current, t_token *head)
{
	if ((*current)->is_space == -1 && (*current)->next)
	{
		(*current)->value = ft_strjoin_((*current)->value,
				(*current)->next->value);
		(*current)->is_space = (*current)->next->is_space;
		remove_token(&head, (*current)->next);
		return (1);
	}
	return (0);
}

void	set_command_name(t_commande_state *state, t_token *current,
    int *found_cmd_name)
{
if (!(*found_cmd_name))
{
    state->current_cmd->name = ft_strdup(current->value);
    *found_cmd_name = 1;
}
}
bool check_current_type(enum e_token_type type)
{
	return (type == TOKEN_RED_IN || type == TOKEN_HERDOC
			|| type == TOKEN_RED_OUT || type == TOKEN_APPEND
			|| type == TOKEN_RED_INOUT);
}



