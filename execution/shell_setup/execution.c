#include "mini_shell.h"

#include "mini_shell.h"

void    execution(t_setup *setup)
{
    // int     pid;
    char    *path;

    if (command_type(setup->cmd->name))
        built_ins(setup); // >>> just for the test the built_ins
    else
    {
        path = get_path(setup);
        if (!path)
            ft_perror("command not found.\n", 999); // >>> exit status litter on.
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
