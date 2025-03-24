#include "mini_shell.h"

void	execute_internal(t_command *cmd, t_setup *setup)
{
	if (ft_strcmp(cmd->name, "echo") == 0)
		echo_cmd(setup);
	else if (ft_strcmp(cmd->name, "cd") == 0)
		cd_cmd(setup);
	else if (ft_strcmp(cmd->name, "pwd") == 0)
		pwd_cmd(setup);
    else if (ft_strcmp(cmd->name, "unset") == 0)
			unset_cmd(&setup->env, cmd->args[1]);
    else if (ft_strcmp(cmd->name, "env") == 0)
		env_cmd(setup);
    else if (ft_strcmp(cmd->name, "exit") == 0)
	    exit_cmd(setup);
    else if (ft_strcmp(cmd->name, "export") == 0) // >>> []
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

int command_type(char *name)
{
    if (is_built_in(name))
        return (BUILT_IN);
    return (EXTERNAL);
}
