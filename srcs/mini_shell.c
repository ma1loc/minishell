# include "mini_shell.h"
# include "../parsing/tokenizer.h"

<<<<<<< HEAD
t_set_env  *init_struct()
{
    t_set_env  *set_env;

    set_env = malloc(sizeof(t_set_env));
    if (!set_env)
        return (NULL);
    set_env->input = NULL;
    set_env->env = NULL;
    set_env->token = NULL;
    set_env->cmd = NULL;
    set_env->pwd = NULL;
    set_env->oldpwd = NULL;
    set_env->env_split = NULL;
    set_env->env_list = NULL;

    return (set_env);
}

void	built_ins(t_set_env *built_in)
{
	// >>> build-ins.
    // int i = 0;
	// while (built_in->cmd->args[i])
	// {
	// 	printf("%s\n", built_in->cmd->args[i]);
    //     i++;
	// }
    // printf("built_in->cmd->args[0] -> %s\n", built_in->cmd->args[0]);
    // printf("built_in->cmd->args[1] -> %s\n", built_in->cmd->args[1]);
	if (ft_strcmp(built_in->cmd->name, "echo") == 0)    // >>> [DONE]
		echo_cmd(built_in);
	else if (ft_strcmp(built_in->cmd->name, "cd") == 0)    // >>> [DONE]
		cd_cmd(built_in);
	else if (ft_strcmp(built_in->cmd->name, "pwd") == 0)  // >>> [DONE]
		pwd_cmd(built_in);
    else if (ft_strcmp(built_in->cmd->name, "unset") == 0)   // >>> [DONE]
	{
		if (built_in->cmd->args[1] == NULL)
			printf("few unset args !!!\n");
		else
			unset_cmd(&built_in->env_list, built_in->cmd->args[1]);
	}
    else if (ft_strcmp(built_in->cmd->name, "env") == 0)    // >>> [DONE]
		env_cmd(built_in);
	
    // else if (ft_strncmp(built_in->cmd->name, "exit", 4) == 0)
	//     exit_cmd(built_in);

}

int		main(int argc, char **argv, char **env)
{
    (void)argv;
    t_set_env  *setup_env;

    // >>> setup the env
    setup_env = init_struct();
    setup_env->env_list = init_env(env, setup_env); // seg to fix
    get_pwd(setup_env);
    set_env(&setup_env->env_list, "OLDPWD", setup_env->pwd); // here a seg
    // <<<

    if (argc == 1)
    {
=======
int main(int argc, char **argv, char **env)
{
    (void)argv;
    char    *input;
    t_env   *set_env;

    input = NULL;
    set_env = init_env(env);
    if (argc == 1)
    {
<<<<<<< HEAD
=======
        signal(SIGINT, signals); // 'ctrl + c'
        signal(SIGQUIT, signals); // 'ctrl + \' // >>> (does nothing fix).
        // char *args[] = {input, NULL };
>>>>>>> 4b13520 (update)
>>>>>>> 0ce570e13e4b0b223063194c26e845647d18e9d8
        while (1)
        {
            setup_env->input = readline("minishell$ ");
            if (setup_env->input == NULL)
                break;
<<<<<<< HEAD
            setup_env->token = tokenize(setup_env->input);
            setup_env->cmd = pars_tokens(setup_env->token);
			built_ins(setup_env);
			add_history(setup_env->input);
=======

<<<<<<< HEAD
=======
            // >>> parsing (tokenization)
                // will start here.
                // just to take an image.
            // <<<

>>>>>>> 4b13520 (update)
            // >>> build-ins.
            if (ft_strncmp(input, "echo", 4) == 0)
                echo_cmd(input);
            if (ft_strncmp(input, "cd", 2) == 0)
                cd_cmd(input);
            if (ft_strncmp(input, "pwd", 3) == 0)
                pwd_cmd(input);
            if (ft_strncmp(input, "exit", 4) == 0)
                exit_cmd();    
            if (ft_strncmp(input, "env", 3) == 0)
<<<<<<< HEAD
                env_cmd(set_env);
            if (ft_strncmp(input, "unset", 5) == 0)
            {
                char **inp = ft_split(input, ' ');
                if (inp[1] == NULL)
                    printf("few unset args !!!\n");
                else
                    unset_cmd(&set_env, inp[1]);
            }
=======
                env_cmd(env);
>>>>>>> 4b13520 (update)
>>>>>>> 0ce570e13e4b0b223063194c26e845647d18e9d8
        }
    }
    else
    {
        printf("RUN './minishell' with no extra args, please ;)\n");
        exit(1);
    }
    return 0;
}
<<<<<<< HEAD
=======

<<<<<<< HEAD
=======


            // env_cmd(input, env);
            // pwd_cmd(input);
            // cd_cmd(input);
            // exit_cmd(input);
            
            // here >>> add the input from the readline in the history buffer
            // check for not include the enter lines in the history (just valid input)
            // add_history(input); allocates memory for storing the command
            // if (input && *input)
            //     add_history(input);
			// rl_clear_history();

			// test
			// t_env *done_env;
			// done_env = env_split(env);
			// while (done_env)
			// {
			// 	printf("%s", done_env->key);
			// 	printf("=");
			// 	printf("%s", done_env->value);
			// 	done_env = done_env->next;
			// }
            // free(input);
            // exit(111);
        // }
>>>>>>> 4b13520 (update)
>>>>>>> 0ce570e13e4b0b223063194c26e845647d18e9d8
