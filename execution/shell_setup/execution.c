#include "mini_shell.h"

// check if there's a pipe and then check the rediraction
// void    execute_cmd(t_setup *setup)
void    execute_cmd(t_setup *setup)
{
    int pid;

    pid = fork();
    if (pid == -1)
        return ;
    if (pid > 0)
        wait(&pid);
    if (execve(setup->cmd_path, setup->cmd->args, NULL) == -1)  // set the env here
        printf("execute cmd will be done here\n");
    // if (execve(path, setup->cmd->args, setup->) == -1)
}

void    execution(t_setup *setup)
{
    if (setup->cmd->type == TOKEN_WORD && is_built_in(setup->cmd->name))
        built_ins_cmd(setup);
    setup->cmd_path = path_resolver(setup);
    if (!setup->cmd_path)
        printf("path -> NULL\n");
    // external_cmd(setup);
    
}
