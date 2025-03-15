#include "mini_shell.h"

// check if there's a pipe and then check the rediraction
// void    execute_cmd(t_setup *setup)
void    execute_cmd(t_setup *setup, char *path)
{
    int pid;

    pid = fork();
    if (pid == -1)
        return ;
    if (pid > 0)
        wait(&pid);
    if (execve(path, setup->cmd->args, NULL) == -1)
        printf("execute cmd will be done here\n");
    // if (execve(path, setup->cmd->args, setup->) == -1)
}

void    execution(t_setup *setup)
{
    // int     pid;
    char    *path;

    // printf("cmd -> %u\n", setup->cmd->type);    // -> 0
    // printf("word_token -> %u\n", TOKEN_WORD);   // -> 1
    // // if (is_built_in(setup->cmd->name))
    // if (is_built_in(setup->cmd->name) && setup->cmd->type == TOKEN_WORD)
    //     built_ins(setup);
    if (setup->cmd->type == TOKEN_WORD && is_built_in(setup->cmd->name))
        built_ins(setup);
    else
    {
        path = get_path(setup);
        if (!path)
            ft_perror("minishell: command not found\n", 999);
        // else
        //     execute_cmd(setup, path);
    }
}
