# include "mini_shell.h"
# include "../parsing/tokenizer.h"

int		main(int argc, char **argv, char **env)
{
    (void)argv;
    t_setup  *setup;

    setup = NULL;
    if (argc == 1)
    {
        while (true)
        {
            setup = shell_env_setup(env);
            setup->input = readline("minishell$ ");
            if (setup->input == NULL)
                break ;  // >>> for segnal case to free litter on
            if (setup->input[0] == '\0')
                continue ;
            setup->token = tokenize(setup->input);
            if (!setup->token)
                exit(1);
            setup->cmd = pars_tokens(setup->token);
            setup->tree = build_tree_commande(setup->cmd);
            execution(setup->tree, setup);

			add_history(setup->input);
        }
    }
    else
        ft_perror(setup, "No extra args, please ;)\n", 1); // exit status litter on
    return 0;
}
