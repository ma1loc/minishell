# include "mini_shell.h"

// >>> here i have to get the path of the command, i mean the path the 
// will the cmd will be there and executed.

void	free_spliting(char **split_path)
{
	int	i;

	i = 0;
	while (split_path[i])
		free(split_path[i++]);
	free(split_path);
}

char	*split_path(char *path, char *cmd)
{
	int		i;
	char	**split_path;
	char	*add_to_path;
	char	*full_path;

	split_path = ft_split(path + 5, ':');
	if (!split_path)
		return (NULL);
	i = 0;
	while (split_path[i])
	{
		add_to_path = ft_strjoin(split_path[i], "/");
		full_path = ft_strjoin(add_to_path, cmd);
		free(add_to_path);
		if (access(full_path, F_OK | X_OK) == 0)
			return (free_spliting(split_path), full_path);
		free(full_path);
		i++;
	}
	return (free_spliting(split_path), NULL);
}

// >>> executable verification <<<
// 		bash exe/
// 		exe/: exe/: Is a directory <<< exit status 126
//		Command not found	127
// 		Permission denied	
// 		Is a directory		126

// >>> check if path is a directory
int		is_directory(t_setup *setup, char *cmd_path)
{
	int	status;
	struct stat st;

	status = stat(cmd_path, &st);
	if (status == 0 && S_ISDIR(st.st_mode))
	{
		// >>> here i have to set the exit status of 126 litter on
		ft_perror(setup ,"Error: Is a directory\n", CMD_NOT_EXEC);
		return (false);
	}
	return (true);
}

char	*path_resolver(t_setup *setup)
{
	char	*path;
	char	*cmd;
	t_env	*env_list;

	path = NULL;
	cmd = setup->cmd->name;
	env_list = setup->env;
	if (is_directory(setup, cmd) == false)
		return (NULL);
	else if (ft_strchr(cmd, '/') != NULL)
		return (ft_strdup(cmd));
	else if (access(cmd, F_OK | X_OK) == 0)	
		return (ft_strdup(cmd));
    while (env_list && ft_strcmp(env_list->key, "PATH") != 0)
		env_list = env_list->next;
	if (!env_list)
		return (NULL);
	path = split_path(env_list->value, cmd);
	if (!path)
		return (ft_perror(setup, "Error: command not found\n", FAIL), NULL);
	return (path);
}
