/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:47:40 by yanflous          #+#    #+#             */
/*   Updated: 2025/04/22 18:47:44 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	unset_key(t_setup *setup, char *key)
{
	t_env	*curr;
	t_env	*prev;

	if (!setup->env || !key)
		return ;
	curr = setup->env;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev == NULL)
				setup->env = curr->next;
			else
				prev->next = curr->next;
			gc_free(g_gc, curr->key);
			if (curr->value)
				gc_free(g_gc, curr->value);
			gc_free(g_gc, curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	unset_cmd(t_setup *setup)
{
	char	**args;
	int		i;

	i = 1;
	args = setup->cmd->args;
	if (!args[1])
		return (setup->exit_stat = 0, (void)0);
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			i++;
			continue ;
		}
		unset_key(setup, args[i]);
		i++;
	}
	setup->exit_stat = 0;
}
