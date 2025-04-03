# include "mini_shell.h"
# include "../parsing/tokenizer.h"

// >>> minishell header
// >>> heredoc have to be form A-Z order
// adsf | ls | eadsf >>> test the exit status of it 
// < Makefile > 5
// ls >
// ls || cat


t_setup	*start_setup(int argc, char **argv, char **env)
{
	(void)argv;
	t_setup	*setup;

	setup = NULL;
    if (argc > 1)	// >>> check this will inter or not >>>>
	{
        ft_perror(NULL, "No extra args, please ;)\n", EXIT_FAILURE); // exit status litter on
		return (NULL);
	}
    setup = shell_env_setup(env);
	if (!setup)
		return (NULL);
	setup->envp = env;
	return (setup);
}

int		main(int argc, char **argv, char **env)
{
    t_setup  *setup;

    setup = start_setup(argc, argv, env);
	if (!setup)
		return (1);
    while (true)
    {
        setup->input = readline("minishell$ ");
        if (setup->input == NULL)
            break ;  // >>> for segnal case to free litter on
        if (setup->input[0] == '\0')
            continue ;
        setup->token = tokenize(setup);
        if (!setup->token)
			continue ;
        setup->cmd = pars_tokens(setup->token);
        setup->tree = build_tree_commande(setup->cmd);
		// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		process_heredoc(setup->tree, setup);
		setup->i = 0;
		// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        execution(setup->tree, setup);
		add_history(setup->input);
		free(setup->input);
    }
    return 0;
}
