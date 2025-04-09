# include "mini_shell.h"
# include "../parsing/tokenizer.h"

// >>> minishell header
// >>> heredoc have to be form A-Z order
// adsf | ls | eadsf >>> test the exit status of it 
// < Makefile > 5
// < Makefile | cat >>> segv
// ls || cat >>> segv
// ls >
// < Makefile > 5 << l cat >>> delimiter problem
// echo $? >>> not working
// Makefile > cat
// export a="ls |cat"
// minishell$ cat << EOF | grep success | tee output.txt | wc -l >> log.txt
// export a+="hello_world" -> to fix later on
// ls   -la >>> command not found in tab char and newline
// is i have to update the SHLVL=1???
// env -i ./minishell
// echo yassin > a > b >c > /dev/stdout

t_setup	*start_setup(int argc, char **argv, char **env, t_gc *gc)
{
	(void)argv;
	t_setup	*setup;

	setup = NULL;
    if (argc > 1)
	{
        ft_perror(NULL, "No extra args, please ;)\n", EXIT_FAILURE); // >>> exit status litter on
		return (NULL);
	}
    setup = shell_env_setup(env, gc);
	if (!setup)
		return (NULL);	// >>> here i have to free and exit;
	setup->envp = env;
	return (setup);
}

int		main(int argc, char **argv, char **env)
{
    t_setup			*setup;
	t_gc			*gc;

	gc = gc_init();
    setup = start_setup(argc, argv, env, gc);
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
        if (!setup->token || ft_strlen(setup->token->value) == 0)
			continue ;
		setup->cmd = pars_tokens(setup);
        setup->tree = build_tree_commande(setup->cmd);
		heredoc_process(setup, setup->tree, gc);
        execution(setup->tree, setup, gc);
		add_history(setup->input);
		free(setup->input);
    }
	gc_destroy(gc);
    return 0;
}
