# include "mini_shell.h"
# include "../parsing/tokenizer.h"

// >>> minishell header
int		main(int argc, char **argv, char **env)
{
    (void)argv;
    t_setup  *setup;

    setup = NULL;
    if (argc > 1)
        ft_perror(NULL, "No extra args, please ;)\n", EXIT_FAILURE); // exit status litter on
    setup = shell_env_setup(env);
    setup->envp = env;
	
    while (true)
    {
        setup->input = readline("minishell$ ");
        if (setup->input == NULL)
            break ;  // >>> for segnal case to free litter on
        if (setup->input[0] == '\0')
            continue ;
        setup->token = tokenize(setup->input, setup);
		setup->token = expand_env_vars(setup->token, setup);
        if (!setup->token)
			continue ;
            // exit(EXIT_FAILURE);
        setup->cmd = pars_tokens(setup->token);
        setup->tree = build_tree_commande(setup->cmd);
        execution(setup->tree, setup);
		add_history(setup->input);
		free(setup->input);
    }
    return 0;
}
