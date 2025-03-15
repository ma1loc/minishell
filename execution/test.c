#include "mini_shell.h"

int execute_command(t_setup *setup)
{
    char *cmd_path;
    int status;
    
    if (!setup->cmd || !setup->cmd->name)
        return (0);
    
    if (is_builtin(setup->cmd->name))
    {
        return (execute_builtin(setup));
    }
    
    cmd_path = get_path(setup);
    if (!cmd_path)
    {
        ft_putstr_fd("minishell: command not found: ", 2);
        ft_putendl_fd(setup->cmd->name, 2);
        return (127);
    }
    
    status = execute_external(setup, cmd_path);
    free(cmd_path);
    return (status);
}


// int execute_command_tree(t_command *cmd, int input_fd, int output_fd)
// {
//     if (!cmd)
//         return (SUCCESS);
        
//     if (cmd->type == TOKEN_CMD) {
//         // Execute simple command, checking if built-in
//         if (is_builtin(cmd->content))
//             return (execute_builtin(cmd->content, input_fd, output_fd));
//         else
//             return (execute_external(cmd->content, input_fd, output_fd));
//     }
//     else if (cmd->type == TOKEN_PIPE) {
//         int pipe_fd[2];
//         if (pipe(pipe_fd) == -1)
//             return (ERROR);
            
//         // Execute left side of pipe, output goes to pipe
//         int ret = execute_command_tree(cmd->left, input_fd, pipe_fd[1]);
//         close(pipe_fd[1]);
        
//         if (ret != SUCCESS)
//             return (ret);
            
//         // Execute right side of pipe, input comes from pipe
//         ret = execute_command_tree(cmd->right, pipe_fd[0], output_fd);
//         close(pipe_fd[0]);
        
//         return (ret);
//     }
//     // Add other token types as needed
    
//     return (SUCCESS);
// }