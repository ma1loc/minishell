# include "mini_shell.h"
# include "../parsing/tokenizer.h" // to change

int		main(int argc, char **argv, char **env)
{
    (void)argv;
    t_setup  *setup_env;

    setup_env = NULL;
    if (argc == 1)
    {
        while (true)
        {
            setup_env = shell_env_setup(env);
            setup_env->input = readline("minishell$ ");
            if (setup_env->input == NULL)
                break;  // >>> for segnal case to free litter on
            if (setup_env->input[0] == '\0')
                continue;
            setup_env->token = tokenize(setup_env->input);
            if (!setup_env->token)
                exit(1);
            setup_env->cmd = pars_tokens(setup_env->token);
            execution(setup_env);
			add_history(setup_env->input);
        }
    }
    else
        ft_perror("No extra args, please ;)\n", 999); // exit status litter on
    return 0;
}
