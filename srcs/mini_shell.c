# include "mini_shell.h"
# include "../parsing/tokenizer.h"
void	built_ins(t_env *env, t_command *cmd)
{
	// >>> build-ins.
	// while (*cmd->args)
	// {
	// 	printf("%s\n", *cmd->args);
	// 	cmd->args++;
	// }
	if (ft_strcmp(cmd->name, "echo") == 0)
		echo_cmd(cmd);
	// else if (ft_strncmp(cmd->name, "cd", 2) == 0)
	// 	cd_cmd(input);
	// else if (ft_strncmp(cmd->name, "pwd", 3) == 0)
	// 	pwd_cmd(input);
	// else if (ft_strncmp(cmd->name, "unset", 5) == 0)
	if (ft_strcmp(cmd->name, "unset") == 0)
	{
		if (cmd->args[1] == NULL)
			printf("few unset args !!!\n");
		else
			unset_cmd(&env, cmd->args[1]);
	}
	else if (ft_strcmp(cmd->name, "env") == 0)
		env_cmd(env);
	// else if (ft_strncmp(input, "exit", 4) == 0)
	//     exit_cmd();    
}
int		main(int argc, char **argv, char **env)
{
    (void)argv;
    char    *input;
    t_env   *set_env;
    t_token *token;
    t_command *cmd;

    input = NULL;
    token = NULL;
    cmd = NULL;
    set_env = init_env(env);
    if (argc == 1)
    {
        while (1)
        {
            input = readline("minishell$ "); // prompt && take input 
            if (input == NULL)
                break;
            token = tokenize(input);
            cmd = pars_tokens(token);
			built_ins(set_env, cmd);
			add_history(input);	// have to free with [rl_clear_history] litter
			
			
        }
    }
    else
    {
        printf("RUN './minishell' with no extra args, please ;)\n");
        exit(1);
    }
    return 0;
}
