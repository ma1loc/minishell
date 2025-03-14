#include "mini_shell.h"

// check if there's a pipe and then check the rediraction
void    execution(t_setup *setup)
{
    // int     pid;
    char    *path;

    // printf("cmd -> %u\n", setup->cmd->type);    // -> 0
    // printf("word_token -> %u\n", TOKEN_WORD);   // -> 1
    // if (is_built_in(setup->cmd->name))
    if (is_built_in(setup->cmd->name) && setup->cmd->type == TOKEN_WORD)
        built_ins(setup);
    else
    {
        // printf("else\n");
        if (setup->cmd->type == TOKEN_PIPE)
        {
            printf("there pipe\n");
            printf("%s\n", setup->cmd->name);
            printf("%s\n", setup->cmd->next->name);
            return ;
        }
        path = get_path(setup);
        if (!path)
            return ;
        // external();  // >>> this is the execution part
    }

    // if (command_type(setup->cmd->name) == BUILT_IN)
    // else
    // {
    //     // execution(setup_env);
    //     if (setup->cmd->redirections->type == TOKEN_HERDOC)
    //         heredoc(setup);
    //     // else if if (setup_env->cmd->type == TOKEN_HERDOC)
    // }
}
