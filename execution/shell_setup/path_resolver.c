# include "mini_shell.h"

//	>>> here i have to get the path of the command, i mean the path the 
//	will the cmd will be there and executed.

char	*split_path(char *path, char *cmd, t_gc *gc)
{
	int		i;
	char	**split_path;
	char	*add_to_path;
	char	*full_path;

	split_path = ft_split(path, ':', gc);
	if (!split_path)
		allocation_failed_msg(gc);
	i = 0;
	while (split_path[i])
	{
		add_to_path = ft_strjoin(split_path[i], "/", gc);
		full_path = ft_strjoin(add_to_path, cmd, gc);
		if (!add_to_path || !full_path)
			allocation_failed_msg(gc);
		gc_free(gc, add_to_path);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		gc_free(gc, full_path);
		i++;
	}
	return (NULL);
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
		return (1);
	}
	return (0);
}

char	*is_valid_str(char *cmd, t_gc *gc)
{
	char	*dup;

	dup = NULL;
	// if ((ft_strchr(cmd, '/') != NULL) || (access(cmd, F_OK | X_OK == 0)))
	if ((ft_strchr(cmd, '/') != NULL) || (access(cmd, F_OK | X_OK) == 0))

	{
		dup = ft_strdup(cmd, gc);
		if (!dup)
			allocation_failed_msg(gc);
		return (dup);
	}
	return (NULL);
}

char	*path_resolver(t_setup *setup, t_gc *gc)
{
	char	*path;
	char	*cmd;
	char	*dup;
	t_env	*env_list;

	dup = NULL;
	path = NULL;
	cmd = setup->cmd->name;
	env_list = setup->env;
	if (is_directory(setup, cmd))
		return (NULL);
	dup = is_valid_str(cmd, gc);
	if (dup)
		return (dup);
    while (env_list && ft_strcmp(env_list->key, "PATH") != 0)
		env_list = env_list->next;
	if (!env_list)
		return (NULL);
	path = split_path(env_list->value, cmd, gc);
	if (!path)
		return (NULL);
	return (path);
}
