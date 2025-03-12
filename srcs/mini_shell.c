# include "mini_shell.h"
# include "../parsing/tokenizer.h" // to change

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// void print_minishell(void)
// {
//     printf("███╗   ███╗██╗███╗  ██╗██╗ ██████╗"\/
//     "  ██╗  ██╗███████╗██╗     ██╗     \n");
//     printf("████╗ ████║██║████╗ ██║██║██╔════╝" \/
//     " ██║  ██║██╔════╝██║     ██║     \n");
//     printf("██╔████╔██║██║██╔██╗██║██║███████╗ "\/
//     " ███████║█████╗  ██║     ██║          by:\n");
//     printf("██║╚██╔╝██║██║██║╚████║██║╚════██╗ "\/
//     " ██╔══██║██╔══╝  ██║     ██║          @ma1loc\n");
//     printf("██║ ╚═╝ ██║██║██║ ╚███║██║███████╔╝"\/
//     " ██║  ██║███████╗███████╗███████╗     @X-Hunter\n");
//     printf("╚═╝     ╚═╝╚═╝╚═╝  ╚══╝╚═╝╚══════╝ "\/
//     " ╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"\/
//     "     date: March 10, 2025\n");
// }
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

t_setup  *init_setup_struct()
{
    t_setup  *set_env;

    set_env = malloc(sizeof(t_setup));
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
    set_env->exit_status = 0;   // >>> to see litter on

    return (set_env);
}

void	built_ins(t_setup *built_in)
{
	if (ft_strcmp(built_in->cmd->name, "echo") == 0)    // >>> [Done]
		echo_cmd(built_in);
	else if (ft_strcmp(built_in->cmd->name, "cd") == 0)    // >>> [Done]
		cd_cmd(built_in);
	else if (ft_strcmp(built_in->cmd->name, "pwd") == 0)  // >>> [Done]
		pwd_cmd(built_in);
    else if (ft_strcmp(built_in->cmd->name, "unset") == 0)   // >>> [Done]
			unset_cmd(&built_in->env_list, built_in->cmd->args[1]);
    else if (ft_strcmp(built_in->cmd->name, "env") == 0)    // >>> [Done]
		env_cmd(built_in);
    else if (ft_strcmp(built_in->cmd->name, "exit") == 0)   // >>> [D]
	    exit_cmd(built_in);
    // else if (ft_strcmp(built_in->cmd->name, "Export") == 0) // >>> [D]
        // >>> export latter on <<<

}

// >>> setup the env of the minishell
t_setup *shell_env_setup(char **env)
{
    t_setup  *setup_env;

    setup_env = init_setup_struct();
    if (!setup_env)
        ft_perror("memory allocation failed\n", FAIL);
    setup_env->env_list = init_env(env, setup_env);
    if (!setup_env->env_list)
        ft_perror("cd: memory allocation failed\n", FAIL); // to free latter on
    get_pwd(setup_env);
    set_env(&setup_env->env_list, "OLDPWD", setup_env->pwd);

    return (setup_env);
}

int		main(int argc, char **argv, char **env)
{
    (void)argv;
    t_setup  *setup_env;

    setup_env = NULL;
    if (argc == 1)
    {
        while (1)
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
            // here i have to know the command type.
			built_ins(setup_env); // just for the test the built_ins
			add_history(setup_env->input);
        }
    }
    else
        ft_perror("No extra args, please ;)\n", FAIL);
    return 0;
}
