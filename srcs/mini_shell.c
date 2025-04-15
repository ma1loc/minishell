# include "mini_shell.h"
# include "../parsing/tokenizer.h"

t_gc *gc = NULL;

void	start_execution(t_setup *setup)
{
	if (is_heredoc(setup->tree))
	{
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

void	sigint_exit_status(t_setup *setup)
{
	setup->exit_stat = *exit_status();
	*exit_status() = 0;
}

int	main(int argc, char **argv, char **env)
{
    t_setup	*setup;

    setup = start_setup(argc, argv, env);
	if (!setup)
		return (1);
    while (true)
    {
		signal(SIGINT, main_sigint);
		signal(SIGQUIT, SIG_IGN);
		setup->input = readline("minishell$ ");
		if (*exit_status() == EXIT_SEGINT)	// ctrl + C
			sigint_exit_status(setup);
        if (setup->input == NULL)	// ctrl + D
			do_eof(setup);
		add_history(setup->input);
        setup->token = tokenize(setup);
        if (!setup->token || ft_strlen(setup->token->value) == 0)
			continue ;
		setup->cmd = pars_tokens(setup);
        setup->tree = build_tree_commande(setup->cmd);
		printf("args[0] -> %s\n", setup->cmd->args[0]);
		printf("args[1] -> %s\n", setup->cmd->args[1]);
		printf("args[2] -> %s\n", setup->cmd->args[2]);
		start_execution(setup);
		free(setup->input);
    }
    return (0);
}
