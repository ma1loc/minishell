#include "mini_shell.h"

void	built_ins(t_setup *built_in)
{
	if (ft_strcmp(built_in->cmd->name, "echo") == 0)    // >>> [Done]
		echo_cmd(built_in);
	else if (ft_strcmp(built_in->cmd->name, "cd") == 0)    // >>> [Done]
		cd_cmd(built_in);
	else if (ft_strcmp(built_in->cmd->name, "pwd") == 0)  // >>> [Done]
		pwd_cmd(built_in);
    else if (ft_strcmp(built_in->cmd->name, "unset") == 0)   // >>> [Done]
			unset_cmd(&built_in->env_list, built_in->cmd->args[1]);
    else if (ft_strcmp(built_in->cmd->name, "env") == 0)    // >>> [Done]
		env_cmd(built_in);
    else if (ft_strcmp(built_in->cmd->name, "exit") == 0)   // >>> [D]
	    exit_cmd(built_in);
    else if (ft_strcmp(built_in->cmd->name, "export") == 0) // >>> []
        export_cmd(built_in);
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
