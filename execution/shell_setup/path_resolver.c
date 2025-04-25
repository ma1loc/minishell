/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:23:21 by yanflous          #+#    #+#             */
/*   Updated: 2025/04/23 09:23:26 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*split_path(char *path, char *cmd)
{
	int		i;
	char	**split_path;
	char	*add_to_path;
	char	*full_path;

	split_path = ft_split(path, ':');
	if (!split_path)
		allocation_failed_msg();
	i = 0;
	while (split_path[i])
	{
		add_to_path = ft_strjoin(split_path[i], "/");
		full_path = ft_strjoin(add_to_path, cmd);
		if (!add_to_path || !full_path)
			allocation_failed_msg();
		gc_free(g_gc, add_to_path);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		gc_free(g_gc, full_path);
		i++;
	}
	return (NULL);
}

int	is_directory(t_setup *setup, char *cmd_path)
{
	int			status;
	struct stat	st;

	status = stat(cmd_path, &st);
	if (status == 0 && S_ISDIR(st.st_mode))
	{
		ft_perror(setup, "Error: Is a directory\n", CMD_NOT_EXEC);
		return (1);
	}
	return (0);
}

char	*is_valid_str(char *cmd)
{
	char	*dup;

	dup = NULL;
	if ((ft_strchr(cmd, '/') != NULL) && (access(cmd, F_OK | X_OK) == 0))
	{
		dup = ft_strdup(cmd);
		return (dup);
	}
	return (NULL);
}

char	*path_resolver(t_setup *setup)
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
	dup = is_valid_str(cmd);
	if (dup)
		return (dup);
	while (env_list && ft_strcmp(env_list->key, "PATH") != 0)
		env_list = env_list->next;
	if (!env_list)
		return (command_not_found(setup), NULL);
	path = split_path(env_list->value, cmd);
	if (!path)
		return (command_not_found(setup), NULL);
	return (path);
}
