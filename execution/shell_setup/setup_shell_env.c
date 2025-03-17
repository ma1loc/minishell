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
    set_env->exit_status = 0;   // >>> to see litter on
    return (set_env);
}

// >>> setup the env of the minishell
t_setup *shell_env_setup(char **env)
{
    t_setup  *setup_env;

    setup_env = init_setup_struct();
    setup_env->envp = env;  // to check litter on.
    if (!setup_env)
        ft_perror("memory allocation failed\n", FAIL);
    setup_env->env = init_env(env, setup_env->env);
    if (!setup_env->env)
        ft_perror("cd: memory allocation failed\n", FAIL); // to free latter on
    get_pwd(setup_env);
    set_env(&setup_env->env, "OLDPWD", setup_env->pwd);

    return (setup_env);
}
