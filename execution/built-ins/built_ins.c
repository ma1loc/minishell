#include "mini_shell.h"

void	execute_internals(t_command *cmd, t_setup *setup)
{
	if (ft_strcmp(cmd->name, "echo") == 0)			// >>> [done to check]
		echo_cmd(setup);
	else if (ft_strcmp(cmd->name, "cd") == 0)		// >>> [done to check!!!]
		cd_cmd(setup);
	else if (ft_strcmp(cmd->name, "pwd") == 0)		// >>> [done to check!!!]
		pwd_cmd(setup);
    else if (ft_strcmp(cmd->name, "unset") == 0)	// >>> [done to check!!!]
		unset_cmd(setup);
    else if (ft_strcmp(cmd->name, "env") == 0)		// >>> [done to check]
		env_cmd(setup);
    else if (ft_strcmp(cmd->name, "exit") == 0)		// >>> [done to check!!!]
	    exit_cmd(setup);
    else if (ft_strcmp(cmd->name, "export") == 0)	// >>> [done to check!!!]
        export_cmd(setup);
}

int is_built_in(char *name)  
{
    if (ft_strcmp(name, "echo") == 0)
        return (1);
    else if (ft_strcmp(name, "cd") == 0)
        return (1);
    else if (ft_strcmp(name, "pwd") == 0)
        return (1);
    else if (ft_strcmp(name, "export") == 0)
        return (1);
    else if (ft_strcmp(name, "unset") == 0)
        return (1);
    else if (ft_strcmp(name, "env") == 0)
        return (1);
    else if (ft_strcmp(name, "exit") == 0)
        return (1);
    else
        return (0);
}

// int command_type(char *name)
// {
//     if (is_built_in(name))
//         return (BUILT_IN);
//     return (EXTERNAL);
// }
