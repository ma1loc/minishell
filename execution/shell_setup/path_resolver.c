# include "mini_shell.h"

//	>>> here i have to get the path of the command, i mean the path the 
//	will the cmd will be there and executed.

char	*split_path(char *path, char *cmd)
{
	int		i;
	char	**split_path;
	char	*add_to_path;
	char	*full_path;

	split_path = ft_split(path, ':');
	if (!split_path)
		return (NULL);
	i = 0;
	while (split_path[i])
	{
		add_to_path = ft_strjoin(split_path[i], "/");
		full_path = ft_strjoin(add_to_path, cmd);
		free(add_to_path);
		if (access(full_path, F_OK | X_OK) == 0)
			return (free_the_spliting(split_path), full_path);
		free(full_path);
		i++;
	}
	return (free_the_spliting(split_path), NULL);
}

int		is_directory(t_setup *setup, char *cmd_path)
{
	int	status;
	struct stat st;

	status = stat(cmd_path, &st);
	if (status == 0 && S_ISDIR(st.st_mode))
	{
		// >>> here i have to set the exit status of 126 litter on
		ft_perror(setup ,"Error: Is a directory\n", CMD_NOT_EXEC);
		return (0);
	}
	return (1);
}

char	*path_resolver(t_setup *setup)
{
	char	*path;
	char	*cmd;
	t_env	*env_list;

	path = NULL;
	cmd = setup->cmd->name;
	env_list = setup->env;
	if (is_directory(setup, cmd) == 0)
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
		return (NULL);
	return (path);
}
