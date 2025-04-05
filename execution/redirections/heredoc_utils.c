# include "mini_shell.h"

void	rm_tmp_files(t_setup *setup)
{
	int i;

	i = 0;
	while (setup->heredoc->file_name[i])
	{
		// printf("tmp file[%d] -> %s\n", i, setup->heredoc->file_name[i]);
		unlink(setup->heredoc->file_name[i]);
		free(setup->heredoc->file_name[i]);
		i++;
	}
}

void	close_heredoc_fds(t_setup *setup)
{
	int i;

	i = 0;
	while (setup->heredoc->fd[i])
	{
		// printf("close [%d]\n", i);
		close(setup->heredoc->fd[i]);
		i++;
	}
}

char	*get_file_name(t_setup *setup)
{
	char	*file_num;
	char	*file_name;

	file_num = ft_itoa(setup->i);
	if (!file_num)
		return (NULL);
	file_name = ft_strjoin("/tmp/heredoc", file_num);
	if (!file_name)
	{
		free(file_num);
		return (NULL);
	}
	free(file_num);
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
		return (close_heredoc_fds(setup),free(file_name), 1);
	}
	return (0);
}
