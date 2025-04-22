/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:23:33 by yanflous          #+#    #+#             */
/*   Updated: 2025/04/22 18:23:34 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	update_cd(t_setup *setup, char *old_pwd_value)
{
	update_env(setup, "PWD", setup->pwd);
	update_env(setup, "OLDPWD", old_pwd_value);
	if (setup->oldpwd)
		gc_free(g_gc, setup->oldpwd);
	setup->oldpwd = old_pwd_value;
}

void	cd_cmd(t_setup *setup)
{
	t_env	*pwd_env;
	char	*old_pwd_value;
	int		status;

	pwd_env = get_env_key(setup, "PWD");
	if (!pwd_env)
	{
		ft_perror(setup, "cd: PWD not set in environment\n", EXIT_FAILURE);
		return ;
	}
	old_pwd_value = ft_strdup(pwd_env->value);
	status = cd(setup);
	if (status == 0)
	{
		if (get_pwd(setup) == 0)
			update_cd(setup, old_pwd_value);
		else
			gc_free(g_gc, old_pwd_value);
	}
	else
		gc_free(g_gc, old_pwd_value);
}

int	cd(t_setup *setup)
{
	int		status;
	char	*home;
	char	*path;

	home = NULL;
	path = setup->cmd->args[1];
	if (path == NULL)
	{
		home = getenv("HOME");
		if (!home)
			return (ft_perror(setup, "cd: HOME not set\n", EXIT_FAILURE), -1);
		status = chdir(home);
		if (status == -1)
			return (ft_perror(setup, NULL, EXIT_FAILURE), -1);
	}
	else
	{
		status = chdir(path);
		if (status == -1)
			return (ft_perror(setup, NULL, EXIT_FAILURE), -1);
	}
	return (0);
}
