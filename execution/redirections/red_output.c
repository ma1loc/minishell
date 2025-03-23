#include "mini_shell.h"

// void    red_output(t_tree *tree, t_setup *setup)
// {
// 	printf(">>>>>>>>>> inter red_output\n");

// 	//	echo "hello" > text.txt
// 	int		out_file;
// 	int		dup_stdout;

// 	out_file = open(tree->cmd->redirections->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (out_file == -1)
// 		return (ft_perror(setup, NULL, EXIT_FAILURE), (void)0);
// 	if (tree->cmd->name == NULL)
// 		return (close(out_file), (void)0);
// 	dup_stdout = dup(STDOUT_FILENO);
// 	if (dup_stdout == -1)
// 		return (ft_perror(setup, NULL, EXIT_FAILURE), (void)0);
// 	if (dup2(out_file, STDOUT_FILENO) == -1)
// 		return (ft_perror(setup, NULL, EXIT_FAILURE), (void)0);
// 	close (out_file);
// 	execute_command(tree, setup);
// 	dup2(dup_stdout, STDOUT_FILENO);
// 	close (dup_stdout);
// 	return ;
// }
