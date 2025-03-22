#include "mini_shell.h"

// < should redirect input
// open the file using open() with read permissions.
// redirect stdin to the file using dup2().
// execute the command with execve().
// the file not exitstat (no such file or directory: file.txt) => (exit status with 1)
// < Makefile cat < parsing/main_print_tree.c > 1 < mkm > 2
void	red_input(t_tree *tree, t_setup *setup)
{
	int		in_file;
	int		dup_stdin;

	// in the red_input < the file is read only
	in_file = open(tree->cmd->redirections->file_name, O_RDONLY);
	if (in_file == -1)
		ft_perror(setup, NULL, EXIT_FAILURE);
	if (tree->cmd->name == NULL)
		return (close(in_file), (void)0);
	// >>> have first put a backup of the stdin without losing it
	dup_stdin = dup(STDIN_FILENO);
	// >>>>> | < txt.txt cat | <<<<<
	if (dup2(in_file, STDIN_FILENO) == -1)
		ft_perror(setup, NULL, EXIT_FAILURE);
	close(in_file);
	execute_command(tree, setup);
	dup2(dup_stdin, STDIN_FILENO);
	close(dup_stdin);
}
