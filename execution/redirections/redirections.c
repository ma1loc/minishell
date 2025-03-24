#include "mini_shell.h"

int red_input(t_tree *tree, t_setup *setup, t_redirections *redirection)
{
    printf(">>>>>>>>>>>>> inter red_input\n");
    int in_file;
    
    if (tree->cmd->name == NULL)
        return (-1);
    
    in_file = open(redirection->file_name, O_RDONLY);
    if (in_file < 0)
        return (ft_perror(setup, NULL, EXIT_FAILURE), -1);
    else
    {
        if (dup2(in_file, STDIN_FILENO) == -1)
            return (close(in_file), ft_perror(setup, NULL, EXIT_FAILURE), -1);
        close(in_file);
    }
	printf("in_file fd -> %d\n", in_file);
    return (in_file);
}

int    red_output(t_tree *tree, t_setup *setup, t_redirections *redirections)
{
	printf(">>>>>>>>>> inter red_output\n");

	int		out_file;

	if (tree->cmd->name == NULL)
		return (-1);
	out_file = open(redirections->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out_file < 0)
        return (ft_perror(setup, NULL, EXIT_FAILURE), -1);
    else
    {
        if (dup2(out_file, STDOUT_FILENO) == -1)
			return (close(out_file), ft_perror(setup, NULL, EXIT_FAILURE), -1);
        close(out_file);
    }
	printf("out_file fd -> %d\n", out_file);
	return (out_file);
}

// >>> cases:
// cat < out.txt | grep "CC" > ggg
// cat < out.txt | echo "hello" > ggg
// cat <> bala -> hanging
// >>>>>>>>.... seg to check litter on >>>> bash: syntax error near unexpected token `>>'
void redirections_and_execute(t_tree *tree, t_setup *setup)
{
    int dup_stdin;
    int dup_stdout;
    int in_fd;
    int out_fd;
    t_redirections *current;

	in_fd = 0;
	out_fd = 0;
	dup_stdin = dup(STDIN_FILENO);
	dup_stdout = dup(STDOUT_FILENO);
    current = tree->cmd->redirections;
    while (current != NULL)
    {
        if (current->type == TOKEN_RED_IN)
            in_fd = red_input(tree, setup, current);
        else if (current->type == TOKEN_RED_OUT)
            out_fd = red_output(tree, setup, current);
        current = current->next;
    }
	if (in_fd < 0 || out_fd < 0)
		return ;
	else
		execute_command(tree, setup);
    
    dup2(dup_stdin, STDIN_FILENO);
    dup2(dup_stdout, STDOUT_FILENO);
    close(dup_stdin);
    close(dup_stdout);
}
