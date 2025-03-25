# include "mini_shell.h"

int	write_to_heredoc(t_setup *setup, char *heredoc_file)
{
	int		read_fd;

	read_fd = open(heredoc_file, O_RDONLY);
	if (read_fd == -1)
	{
		unlink(heredoc_file);
		return (ft_perror(setup, "Error: open failed\n", EXIT_FAILURE), -1);
	}
	if (dup2(read_fd, STDIN_FILENO) == -1)
	{
		close(read_fd);
		unlink(heredoc_file);
		return (ft_perror(setup, "Error: dup2 failed\n", EXIT_FAILURE), -1);
	}
	close(read_fd);
	unlink(heredoc_file);
	return (0);
}

// >>> signal handler here to litter on just ignore it now
// int	heredoc(t_tree *tree, t_setup *setup)
// {
//     int     write_fd;
//     char    *input;
// 	char	*heredoc_file;
// 	int		status; 	


// 	status = 0;
// 	heredoc_file = ft_strdup("/home/yanflous/Desktop/minishell/heredoc.txt");
//     write_fd = open(heredoc_file, O_CREAT | O_WRONLY, 0644);
//     if (write_fd == -1)
//         return (free(heredoc_file), ft_perror(setup, "Error: open failed\n", EXIT_FAILURE), -1);
//     while (true)
//     {
//         input = readline("heredoc> ");
//         if (input == NULL || ft_strcmp(input, tree->cmd->redirections->file_name) == 0)
//         {
//             if (tree->cmd->name == NULL) // this is the dilemither
// 			{
// 				unlink(heredoc_file);
// 				return (free(heredoc_file), close(write_fd), -1);
// 			}
//             break;
//         }
//         write(write_fd, input, ft_strlen(input));
//         write(write_fd, "\n", 1);
//     }
// 	close(write_fd);
// 	status = write_to_heredoc(setup, heredoc_file);
// 	return (status);
// }


int heredoc(t_tree *tree, t_setup *setup)
{
    int     write_fd;
    char    *input;
    char    *heredoc_file;

    int     status;

    heredoc_file = ft_strdup("/tmp/minishell_heredoc.txt");
    write_fd = open(heredoc_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (write_fd == -1)
        return (free(heredoc_file), ft_perror(setup, "Error: open failed\n", EXIT_FAILURE), -1);

    while (true)
    {
        input = readline("heredoc> ");
        if (!input || ft_strcmp(input, tree->cmd->redirections->file_name) == 0)
            break;
        write(write_fd, input, ft_strlen(input));
        write(write_fd, "\n", 1);
        free(input);
    }
    free(input);
    close(write_fd);
    free(heredoc_file);
    exit(0);

    status = write_to_heredoc(setup, heredoc_file);
    return status;
}
