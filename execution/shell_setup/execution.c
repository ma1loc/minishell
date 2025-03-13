#include "mini_shell.h"

#include "mini_shell.h"

void    execution(t_setup *setup)
{
    // int     pid;
    char    *path;

    path = get_path(setup->cmd->name, setup->env_split);
    if (path)
        printf("path -> %s\n", path);
    else
        printf("NULL\n");
    // if (command_type(setup->cmd->name) == BUILT_IN)
    //     built_ins(setup); // just for the test the built_ins
    // else
    // {
    //     // execution(setup_env);
    //     if (setup->cmd->redirections->type == TOKEN_HERDOC)
    //         heredoc(setup);
    //     // else if if (setup_env->cmd->type == TOKEN_HERDOC)
    // }
}
