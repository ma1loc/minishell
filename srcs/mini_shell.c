# include "mini_shell.h"
# include "../parsing/tokenizer.h"

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
    int i = 0;
	while (built_in->cmd->args[i])
	{
		printf("%s\n", built_in->cmd->args[i]);
        i++;
	}
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
        while (1)
        {
            setup_env->input = readline("minishell$ ");
            if (setup_env->input == NULL)
                break;
            setup_env->token = tokenize(setup_env->input);
            setup_env->cmd = pars_tokens(setup_env->token);
            printf("built_in->cmd->args[0] -> %s\n", setup_env->cmd->args[0]);
            printf("built_in->cmd->args[1] -> %s\n", setup_env->cmd->args[1]);
			built_ins(setup_env);
			add_history(setup_env->input);
        }
    }
    else
    {
        printf("RUN './minishell' with no extra args, please ;)\n");
        exit(1);
    }
    return 0;
}
