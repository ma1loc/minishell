# include "mini_shell.h"
# include "../parsing/tokenizer.h"

void create_pipe(t_setup *setup, int *fds)
{
    if (pipe(fds) == -1)
    {
        ft_perror(setup, "pipe failed", 1);
        exit(1);
    }
}

pid_t create_fork(t_setup *setup)
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
    {
        ft_perror(setup, "fork failed", 1);
        exit(1);
    }
    return pid;
}

void left_process(t_tree *left, t_setup *setup, int *fds)
{
    // >>> close read end
    close(fds[0]);
    dup2(fds[1], STDOUT_FILENO);
    close(fds[1]);
    
    if (left)
        execute_tree(left, setup);
    
    exit(0);
}

void right_process(t_tree *right, t_setup *setup, int *fds)
{
    // >>> close write end
    close(fds[1]);
    dup2(fds[0], STDIN_FILENO);
    close(fds[0]);
    
    if (right)
        execute_tree(right, setup);
    
    exit(0);
}

int execute_pipe(t_tree *tree, t_setup *setup)
{
    printf(">>> pipe line\n");
    int fds[2];
    pid_t pid1;
    pid_t pid2;
    int status;

    create_pipe(setup, fds);
    
    // >>> left command (writes to pipe)
    pid1 = create_fork(setup);
    if (pid1 == 0)
        left_process(tree->left, setup, fds);
        
    // >>> right command (reads from pipe)
    pid2 = create_fork(setup);
    if (pid2 == 0)
        right_process(tree->right, setup, fds);

    close(fds[0]);
    close(fds[1]);
    
    waitpid(pid1, NULL, 0);
    waitpid(pid2, &status, 0);

    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    else
        return 1;
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#include "mini_shell.h"

void    free_old_envp(t_setup *setup)
{
    int i;

    i = 0;
    while (setup->envp[i])
    {
        free(setup->envp[i]);
        i++;
    }
    free(setup->envp);  // Free the envp array itself
}

int     count_new_envp(t_env *env)
{
    int     env_len;
    t_env   *current_env;

    env_len = 0;
    current_env = env;
    while (current_env)
    {
        current_env = current_env->next;
        env_len++;
    }
    return (env_len);
}

// >>> update if the command that use it is export or unset
// >>> to check litter on the update of the env
char    **upload_env(t_setup *setup)
{
    int     envp_len;
    char    **envp_update;
    t_env   *current_env;
    char    *key;
    char    *full_line;
    int     i;

    if (setup->envp)
        free_old_envp(setup);
    envp_len = count_new_envp(setup->env);
    envp_update = malloc(sizeof(char *) * (envp_len + 1));
    if (!envp_update)
        ft_perror(setup, "Error: malloc failed\n", FAIL);
    i = 0;
    current_env = setup->env;
    while (current_env)
    {
        key = ft_strjoin(current_env->key, "=");
        full_line = ft_strjoin(key, current_env->value);
        free(key);  // Free the key after joining
        envp_update[i] = full_line;
        current_env = current_env->next;
        i++;
    }
    envp_update[i] = NULL;
    return (envp_update);
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#include "mini_shell.h"

void    free_old_envp(t_setup *setup)
{
    int i;

    i = 0;
    while (setup->envp[i])
    {
        free(setup->envp[i]);
        i++;
    }
    free(setup->envp);  // Free the envp array itself
}

int     count_new_envp(t_env *env)
{
    int     env_len;
    t_env   *current_env;

    env_len = 0;
    current_env = env;
    while (current_env)
    {
        current_env = current_env->next;
        env_len++;
    }
    return (env_len);
}

// >>> update if the command that use it is export or unset
// >>> to check litter on the update of the env
char    **upload_env(t_setup *setup)
{
    int     envp_len;
    char    **envp_update;
    t_env   *current_env;
    char    *key;
    char    *full_line;
    int     i;

    if (setup->envp)
        free_old_envp(setup);
    envp_len = count_new_envp(setup->env);
    envp_update = malloc(sizeof(char *) * (envp_len + 1));
    if (!envp_update)
        ft_perror(setup, "Error: malloc failed\n", FAIL);
    i = 0;
    current_env = setup->env;
    while (current_env)
    {
        key = ft_strjoin(current_env->key, "=");
        full_line = ft_strjoin(key, current_env->value);
        free(key);
        envp_update[i] = full_line;
        current_env = current_env->next;
        i++;
    }
    return (envp_update[i] = NULL, envp_update);
}