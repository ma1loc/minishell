# include "mini_shell.h"

// >>> here i have to get the path of the command, i mean the path the 
// will the cmd will be there and executed.

void	split_path_free(char **split_path)
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
			return (split_path_free(split_path), full_path);
		free(full_path);
		i++;
	}
	return (split_path_free(split_path), NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*path;

	if (ft_strnstr(cmd, "/", ft_strlen(cmd)) != NULL)
		return (ft_strdup(cmd));
	else if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	i = 0;
	// while (env[i] && ft_strnstr(env[i], "PATH", 4) == 0)
    while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	path = split_path(env[i], cmd);
	return (path);
}