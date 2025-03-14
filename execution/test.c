#include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <errno.h>


// int g_exit_status = 0;

// void	ft_error(char *cmd, char *arg, char *msg, int status)
// {
// 	g_exit_status = status;
	
// 	if (cmd && arg && msg)
// 		fprintf(stderr, "minishell: %s: %s: %s\n", cmd, arg, msg);
// 	else if (cmd && msg)
// 		fprintf(stderr, "minishell: %s: %s\n", cmd, msg);
// 	else if (msg)
// 		fprintf(stderr, "minishell: %s\n", msg);
	
	

// }


// void	cmd_not_found(char *cmd)
// {
// 	ft_error(cmd, NULL, "command not found", 127);
// }

// void	permission_denied(char *path)
// {
// 	ft_error(path, NULL, "Permission denied", 126);
// }

// void	no_such_file(char *cmd, char *file)
// {
// 	ft_error(cmd, file, "No such file or directory", 127);
// }

// void	syntax_error(char *token)
// {
// 	char error_msg[100];
	
// 	sprintf(error_msg, "syntax error near unexpected token `%s'", token);
// 	ft_error(NULL, NULL, error_msg, 2);
// }

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