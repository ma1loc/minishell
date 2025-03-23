#include "mini_shell.h"

// void handle_redirections(t_tree *tree, t_setup *setup)
// {
// 	t_redirections *current_redirection = tree->cmd->redirections;
// 	while (current_redirection != NULL)
// 	{
// 		if (current_redirection->type == TOKEN_HERDOC)
// 			heredoc(tree, setup);
// 		else if (current_redirection->type == TOKEN_RED_IN)
// 			red_input(tree, setup);
// 		else if (current_redirection->type == TOKEN_APPEND)
// 			red_append(tree, setup);
// 		else if (current_redirection->type == TOKEN_RED_OUT)
// 			red_output(tree, setup);
// 		current_redirection = current_redirection->next;
// 	}
// }

int	red_input(t_tree *tree, t_setup *setup)
{
    printf(">>>>>>>>>>>>> inter red_input\n");
	
	int		in_file;
	
	if (tree->cmd->name == NULL)
		return (-1);

	in_file = open(tree->cmd->redirections->file_name, O_RDONLY);
    if (in_file < 0)
        return (ft_perror(setup, NULL, EXIT_FAILURE), -1);
    else
    {
        if (dup2(in_file, STDIN_FILENO) == -1)
			return (close(in_file), ft_perror(setup, NULL, EXIT_FAILURE), -1);
        close(in_file);
    }
	return (in_file);
}

int    red_output(t_tree *tree, t_setup *setup)
{
	printf(">>>>>>>>>> inter red_output\n");

	int		out_file;

	if (tree->cmd->name == NULL)
		return (-1);
	out_file = open(tree->cmd->redirections->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out_file < 0)
        return (ft_perror(setup, NULL, EXIT_FAILURE), -1);
    else
    {
        if (dup2(out_file, STDOUT_FILENO) == -1)
			return (close(out_file), ft_perror(setup, NULL, EXIT_FAILURE), -1);
        close(out_file);
    }
	return (out_file);
}

// >>> cases:
// cat < out.txt | grep "CC" > ggg
// cat < out.txt | echo "hello" > ggg
// >>>>>>>>.... seg to check litter on >>>> bash: syntax error near unexpected token `>>'

void redirections_and_execute(t_tree *tree, t_setup *setup)
{
    int dup_stdin;
    int dup_stdout;
	int fd;
	
	dup_stdin = dup(STDIN_FILENO);
	dup_stdout = dup(STDOUT_FILENO);
    
    while (tree->cmd->redirections != NULL)
    {
        if (tree->cmd->redirections->type == TOKEN_RED_IN)
			fd = red_input(tree, setup);
        else if (tree->cmd->redirections->type == TOKEN_RED_OUT)
			fd = red_output(tree, setup);
        tree->cmd->redirections = tree->cmd->redirections->next;
    }
	if (fd != -1)
		execute_command(tree, setup);
	close(fd);
    dup2(dup_stdin, STDIN_FILENO);
    dup2(dup_stdout, STDOUT_FILENO);
    close(dup_stdin);
    close(dup_stdout);
}

