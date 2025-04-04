# include "mini_shell.h"

void	close_fds(t_setup *setup)
{
	int i;
	int	count;

	i = 0;
	count = setup->heredoc->count;
	while (i <= count)
	{
		close(setup->heredoc->fd[i]);
		i++;
	}
}

char	*get_file_name(t_setup *setup)
{
	char	*file_num;
	char	*file_name;

	file_num = ft_itoa(setup->heredoc->count);
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
	int	count;

	count = setup->heredoc->count;
	close(setup->heredoc->fd[count]);
	setup->heredoc->fd[count] = open(file_name, O_RDONLY, 0644);
	if (!setup->heredoc->fd[count])
	{
		ft_perror(setup, NULL, EXIT_FAILURE);
		return (close_fds(setup),free(file_name), 1);
	}
	free(file_name);
	return (0);
}