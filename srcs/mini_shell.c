# include "mini_shell.h"
#include "../parsing/tokenizer.h"

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
	}
	else
	{
		setup->i = 0;
		execution(setup->tree, setup);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_setup	*setup;

	setup = start_setup(argc, argv, env);
	if (!setup)
		return (1);
	setup_signals();
	while (true)
	{
		setup->input = readline("minishell$ ");
		if (*exit_status() == EXIT_SEGINT)
			sigint_exit_status(setup);
		if (setup->input == NULL)
			do_eof(setup);
		if (setup->input[0] == '\0')
			continue ;
		setup->token = tokenize(setup);
		if (!setup->token || ft_strlen(setup->token->value) == 0)
			continue ;
		add_history(setup->input);
		setup->cmd = pars_tokens(setup);
		setup->tree = build_tree_commande(setup->cmd);
		start_execution(setup);
		free(setup->input);
	}
	return (0);
}
