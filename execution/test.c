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

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#include "mini_shell.h"

void    set_pipe(t_setup *setup, int *fd)
{
    if (pipe(fd) == -1)
    {
        ft_perror(setup, NULL, FAIL);
        return;
    }
}

pid_t    set_first_fork(t_setup  *setup, int *fd)
{
    pid_t pid1;

    pid1 = fork();
    if (pid1 < 0)
    {
        close(fd[0]);
        close(fd[1]);
        ft_perror(setup, NULL, FAIL);
        return (-1);
    }
    return (pid1);
}
// >>> new one <<<
pid_t    set_second_fork(t_setup  *setup, pid_t pid_1, int *fd)
{
    pid_t   pid_2;
    
    pid_2 = fork();
    if (pid_2 < 0)
    {
        close(fd[0]);
        close(fd[1]);
        waitpid(pid_1, NULL, 0);  // >>> wait for first child
        ft_perror(setup, NULL, FAIL);
        return (-1);
    }
    return (pid_2);
}

void    first_child_process(t_setup *setup, t_tree *tree, int *fd)
{
    // >>> child process - execute left command
    // >>> close read end, redirect stdout to pipe write end
    close(fd[0]);
    if (dup2(fd[1], STDOUT_FILENO) == -1)
    {
        ft_perror(setup, NULL, FAIL);
        exit(FAIL);
    }
    close(fd[1]);
    if (tree->left)
    {
        if (tree->left->type == TOKEN_WORD)
        {
            setup->cmd = tree->left->cmd;
            execute_command(tree->left, setup);
        }
        else
		{
			setup->cmd = tree->left->cmd; // to remove it litter on
            execution(tree->left, setup);
		}
    }
    exit(EXIT_SUCCESS);
}

void    second_child_process(t_setup *setup, t_tree *tree, int *fd)
{
    // >>> child process execute right command
    // >>> close write end, redirect stdin to pipe read end
    close(fd[1]);
    if (dup2(fd[0], STDIN_FILENO) == -1)
    {
        ft_perror(setup, NULL, FAIL);
        exit(FAIL);
    }
    close(fd[0]);
    if (tree->right)
    {
        if (tree->right->type == TOKEN_WORD)
        {
            setup->cmd = tree->right->cmd;
            execute_command(tree->right, setup);
        }
        else
		{
			setup->cmd = tree->right->cmd; // to remove it litter on
            execution(tree->right, setup);
		}
    }
    exit(EXIT_SUCCESS);
}

void    execute_pipe(t_tree *tree, t_setup *setup)
{
    int fd[2];
    pid_t pid_1;
    pid_t pid_2;
    int status;
    
    // >>> seting the pipe
    set_pipe(setup, fd);
    // >>> first child process left side
    pid_1 = set_first_fork(setup, fd);
    if (pid_1 == 0)
        first_child_process(setup, tree, fd);
    // >>> second child process right side
    pid_2 = set_second_fork(setup, pid_1, fd);
    if (pid_2 == 0)
        second_child_process(setup, tree, fd);
    // >>> parent process
    close(fd[0]);
    close(fd[1]);
    // >>> wait for both children to finish
    waitpid(pid_1, &status, 0);
    waitpid(pid_2, &status, 0);
}


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


void execute_pipe(t_tree *tree, t_setup *setup)
{
    int fd[2];
    pid_t pid1, pid2;
    
    pipe(fd);
    
    pid1 = fork();
    if (pid1 == 0)
    {

        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        
        if (tree->left->cmd && tree->left->cmd->redirections)
            handle_redirections(tree->left, setup);
        
        execution(tree->left, setup);
        exit(EXIT_SUCCESS);
    }
    
    pid2 = fork();
    if (pid2 == 0)
    {

        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

        if (tree->right->cmd && tree->right->cmd->redirections)
            handle_redirections(tree->right, setup);
        
        execution(tree->right, setup);
        exit(EXIT_SUCCESS);
    }
    
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

void handle_redirections(t_tree *tree, t_setup *setup)
{
    if (tree->cmd->redirections->type == TOKEN_HERDOC)
        heredoc(tree, setup);
    else if (tree->cmd->redirections->type == TOKEN_RED_IN)
        red_input(tree, setup);
    else if (tree->cmd->redirections->type == TOKEN_APPEND)
        red_append(tree, setup);
    else if (tree->cmd->redirections->type == TOKEN_RED_OUT)
        red_output(tree, setup);
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void print_red(t_tree *tree)
{
	t_redirections *tmp;

	tmp = tree->cmd->redirections;
	while (tmp)
	{
		printf("file name -> %s\n", tmp->file_name);
		// printf("file name -> %s\n", tmp->type);
		if (tmp->type == TOKEN_HERDOC)
			printf("herdoc\n");
		else if (tmp->type == TOKEN_RED_IN)
			printf("red_in\n");
		else if (tmp->type == TOKEN_APPEND)
			printf("append\n");
		else if (tmp->type == TOKEN_RED_OUT)
			printf("red_out\n");
		tmp = tmp->next;
	}
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
