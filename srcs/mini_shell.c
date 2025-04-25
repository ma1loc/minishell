/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:12:28 by yanflous          #+#    #+#             */
/*   Updated: 2025/04/22 11:12:32 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_gc	*g_gc = NULL;

void	start_execution(t_setup *setup)
{
	setup->heredoc_counter = 0;
	if (is_heredoc(setup->tree))
	{
		heredoc_counter(setup, setup->tree);
		if (setup->heredoc_counter > 16)
			maximum_heredoc_msg();
		setup->fork_flag = 1;
		signal(SIGINT, SIG_IGN);
		heredoc_process(setup, setup->tree);
		cleanup_heredoc(setup);
	}
	else
	{
		setup->i = 0;
		execution(setup->tree, setup);
	}
}

char	*readline_free(char *input)
{
	char	*tmp_input;

	tmp_input = ft_strdup(input);
	free(input);
	return (tmp_input);
}

int	main(int argc, char **argv, char **env)
{
	t_setup	*setup;

	setup = start_setup(argc, argv, env);
	if (!setup)
		return (1);
	while (true)
	{
		setup->input = readline("minishell$ ");
		if (setup->input == NULL)
			do_eof(setup);
		setup->input = readline_free(setup->input);
		if (*exit_status() == EXIT_SEGINT)
			sigint_exit_status(setup);
		if (setup->input[0] == '\0')
			continue ;
		add_history(setup->input);
		setup->token = tokenize(setup);
		if (!setup->token || ft_strlen(setup->token->value) == 0)
			continue ;
		setup->cmd = pars_tokens(setup);
		setup->tree = build_tree_commande(setup->cmd);
		*get_setup() = setup;
		start_execution(setup);
	}
	return (gc_destroy(g_gc), 0);
}
