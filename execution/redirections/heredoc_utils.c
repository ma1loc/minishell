# include "mini_shell.h"

void	cleanup_heredoc(t_setup *setup)
{
	int i;

	i = 0;
	if (setup->heredoc->fd[i])
	{
		while (setup->heredoc->fd[i])
		{
			close(setup->heredoc->fd[i]);
			i++;
		}
	}
	i = 0;
	if (setup->heredoc->file_name[i])
	{
		while (setup->heredoc->file_name[i])
		{
			unlink(setup->heredoc->file_name[i]);
			gc_free(gc, setup->heredoc->file_name[i]);
			i++;
		}
	}
}

char	*get_file_name(t_setup *setup)
{
	char	*file_num;
	char	*file_name;

	file_num = ft_itoa(setup->i);
	if (!file_num)
		allocation_failed_msg();
	file_name = ft_strjoin("/tmp/heredoc", file_num);
	if (!file_name)
		allocation_failed_msg();
	gc_free(gc, file_num);
	return (file_name);
}

// >>> refresh the offset of the fd
int	refresh_fds(t_setup *setup, char *file_name)
{
	int i;

	i = setup->i;
	close(setup->heredoc->fd[i]);
	setup->heredoc->fd[i] = open(file_name, O_RDONLY, 0644);
	if (!setup->heredoc->fd[i])
	{
		ft_perror(setup, NULL, EXIT_FAILURE);
		return (cleanup_heredoc(setup), free(file_name),1);
	}
	return (0);
}
