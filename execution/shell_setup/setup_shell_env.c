/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_shell_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:26:32 by yanflous          #+#    #+#             */
/*   Updated: 2025/04/23 09:26:34 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_setup	*init_setup(void)
{
	t_setup	*setup;

	setup = gc_malloc(g_gc, sizeof(t_setup));
	if (!setup)
		allocation_failed_msg();
	ft_memset(setup, 0, sizeof(t_setup));
	return (setup);
}

t_setup	*shell_env_setup(char **env)
{
	t_setup	*setup;

	setup = init_setup();
	setup->env = init_env(env, setup->env);
	setup->exec_env = update_exec_envp(setup, setup->env);
	setup->heredoc = gc_malloc(g_gc, sizeof(t_heredoc));
	if (!setup->heredoc)
		allocation_failed_msg();
	setup->heredoc->delimiter = NULL;
	ft_memset(setup->heredoc->fd, 0, sizeof(setup->heredoc->fd));
	ft_memset(setup->heredoc->file_name, 0, sizeof(setup->heredoc->file_name));
	get_pwd(setup);
	update_env(setup, "PWD", setup->pwd);
	update_env(setup, "OLDPWD", setup->pwd);
	setup->oldpwd = ft_strdup(setup->pwd);
	return (setup);
}

t_setup	*start_setup(int argc, char **argv, char **env)
{
	t_setup	*setup;

	(void)argv;
	setup = NULL;
	if (argc > 1)
	{
		ft_perror(NULL, "No extra args, please ;)\n", EXIT_FAILURE);
		return (NULL);
	}
	g_gc = gc_init();
	setup = shell_env_setup(env);
	setup->envp = env;
	setup_signals();
	return (setup);
}
