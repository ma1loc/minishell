# include "mini_shell.h"
# include "../parsing/tokenizer.h"

t_set_env  *init_set()
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
	// while (built_in->env_list)
	// {
	// 	printf("%s\n", built_in->env_list->value);
	// 	built_in->env_list = built_in->env_list->next;
	// }
	if (ft_strcmp(built_in->cmd->name, "echo") == 0)
		echo_cmd(built_in);  // >>> [DONE]
	else if (ft_strcmp(built_in->cmd->name, "cd") == 0)
		cd_cmd(built_in);    // >>> [DONE]
	else if (ft_strcmp(built_in->cmd->name, "pwd") == 0)
		pwd_cmd(built_in);  // >>> [DONE]
	if (ft_strcmp(built_in->cmd->name, "unset") == 0)   // >>> [DONE]
	{
		if (built_in->cmd->args[1] == NULL)
			printf("few unset args !!!\n");
		else
			unset_cmd(&built_in->env, built_in->cmd->args[1]);
	}
    else if (ft_strcmp(built_in->cmd->name, "env") == 0)
		env_cmd(built_in);

	// else if (ft_strncmp(input, "exit", 4) == 0)
	//     exit_cmd();    
}

int		main(int argc, char **argv, char **env)
{
    (void)argv;
    t_set_env  *set_env;

    set_env = init_set();
    set_env->env_list = init_env(env, set_env);
    if (argc == 1)
    {
        while (1)
        {
            set_env->input = readline("minishell$ ");
            if (set_env->input == NULL)
                break;
            set_env->token = tokenize(set_env->input);
            set_env->cmd = pars_tokens(set_env->token);
			built_ins(set_env);
			add_history(set_env->input);
        }
    }
    else
    {
        printf("RUN './minishell' with no extra args, please ;)\n");
        exit(1);
    }
    return 0;
}
