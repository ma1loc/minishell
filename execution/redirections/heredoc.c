# include "mini_shell.h"

// >>> signal handler here to
int	heredoc(t_tree *tree, t_setup *setup)
{
    int     in_file;
    char    *input;
	char	*path_heredoc_file;

	path_heredoc_file = ft_strdup("/home/yanflous/Desktop/minishell/heredoc.txt");
    in_file = open(path_heredoc_file, O_CREAT | O_RDWR, 0644);
    if (in_file == -1)
        return (free(path_heredoc_file), ft_perror(setup, "Error: open failed\n", EXIT_FAILURE), -1);
    while (true)
    {
        input = readline("heredoc> ");
        if (input == NULL || ft_strcmp(input, tree->cmd->redirections->file_name) == 0)
        {
            if (tree->cmd->name == NULL)
				return (free(path_heredoc_file), close(in_file), -1);
            break;
        }
        write(in_file, input, ft_strlen(input));
        write(in_file, "\n", 1);
    }
	// execute the command with the fds
	if (dup2(in_file, STDIN_FILENO) == -1)
		return (free(path_heredoc_file), close(in_file), ft_perror(setup, NULL, EXIT_FAILURE), -1);
    execute_commands(tree, setup);
    unlink(path_heredoc_file);
	close(in_file);
    return (0);
}
