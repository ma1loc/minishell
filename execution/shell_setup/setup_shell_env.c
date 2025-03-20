# include "mini_shell.h"

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
    set_env->cmd_path = NULL;
    set_env->envp = NULL;
    set_env->exit_stat = 0;   // >>> to see litter on
    return (set_env);
}

// >>> setup the env of the minishell
t_setup *shell_env_setup(char **env)
{
    t_setup  *setup;

    setup = init_setup_struct();
    if (!setup)
        ft_perror(setup, "memory allocation failed\n", FAIL);    
    setup->env = init_env(env, setup->env);
    if (!setup->env)
        ft_perror(setup, "cd: memory allocation failed\n", FAIL); // to free latter on
    get_pwd(setup);
    set_env(&setup->env, "OLDPWD", setup->pwd);

    return (setup);
}
