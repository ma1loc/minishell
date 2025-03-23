#include "mini_shell.h"

// < Makefile cat < parsing/main_print_tree.c > 1 < mkm > 2

// void	red_input(t_tree *tree, t_setup *setup)
// {
// 	printf(">>>>>>>>>>>>> inter red_input\n");
// 	int		in_file;
// 	int		dup_stdin;

// 	in_file = open(tree->cmd->redirections->file_name, O_RDONLY);
// 	if (in_file == -1)
// 		return(ft_perror(setup, NULL, EXIT_FAILURE), (void)0);
// 	if (tree->cmd->name == NULL)
// 		return (close(in_file), (void)0);
// 	dup_stdin = dup(STDIN_FILENO);
// 	if (dup_stdin == -1)
// 		return (ft_perror(setup, NULL, EXIT_FAILURE), (void)0);
// 	if (dup2(in_file, STDIN_FILENO) == -1)
// 		return(ft_perror(setup, NULL, EXIT_FAILURE), (void)0);
// 	close(in_file);
// 	execute_command(tree, setup);
// 	dup2(dup_stdin, STDIN_FILENO);
// 	close(dup_stdin);
// }
