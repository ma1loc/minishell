# include "mini_shell.h"
# include "tokenizer.h"

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

t_setup  *init_struct()
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
    set_env->exit_status = 0;

    return (set_env);
}

void	built_ins(t_setup *built_in)
{
	if (ft_strcmp(built_in->cmd->name, "echo") == 0)    // >>> [D] > exit status to fix
		echo_cmd(built_in);
	else if (ft_strcmp(built_in->cmd->name, "cd") == 0)    // >>> [] > to fix seg
		cd_cmd(built_in);
	else if (ft_strcmp(built_in->cmd->name, "pwd") == 0)  // >>> []
		pwd_cmd(built_in);
    else if (ft_strcmp(built_in->cmd->name, "unset") == 0)   // >>> []
			unset_cmd(&built_in->env_list, built_in->cmd->args[1]);
    else if (ft_strcmp(built_in->cmd->name, "env") == 0)    // >>> []
		env_cmd(built_in);
    else if (ft_strcmp(built_in->cmd->name, "exit") == 0)   // >>> []
	    exit_cmd(built_in);

}

int		main(int argc, char **argv, char **env)
{
    (void)argv;
    t_setup  *setup_env;

    // >>> setup the env of the minishell
    setup_env = init_struct();
    setup_env->env_list = init_env(env, setup_env); // seg to fix
    get_pwd(setup_env);
    set_env(&setup_env->env_list, "OLDPWD", setup_env->pwd); // here a seg
    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    if (argc == 1)
    {
        while (1)
        {
            setup_env->input = readline("minishell$ ");
            if (setup_env->input == NULL)
                break;  // >>> for segnal case
            if (setup_env->input[0] == '\0')
                continue;
            setup_env->token = tokenize(setup_env->input);
            if (!setup_env->token)
                exit(1);
            setup_env->cmd = pars_tokens(setup_env->token);
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
