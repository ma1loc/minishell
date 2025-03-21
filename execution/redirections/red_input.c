#include "mini_shell.h"


// void    execute_external(t_tree *tree, t_setup *setup)
// {
    //     pid_t     pid;
//     int     status;
//     (void)tree;

//     setup->cmd_path = path_resolver(setup);
//     if (!setup->cmd_path)
//     {
//         ft_perror(setup ,"Command not found\n", CMD_NOT_FOUND); // >>> exit status to set litter on
//         return;
//     }
//     pid = fork();
//     if (pid == -1)
//     {
    //         perror("fork");
    //         return;
    //     }    
    //     if (pid == 0)
    //     {
        //         // >>> child process
        //         if (execve(setup->cmd_path, setup->cmd->args, setup->envp) == -1) {
            //             perror("execve");
//             exit(EXIT_FAILURE); // >>> exit status to set litter on
//         }
//         // >>> if not execve succeed
//         exit(EXIT_FAILURE);
//     }
//     else
//     {
    //         // >>> parent process
    //         waitpid(pid, &status, 0);
    //         // >>> save exit status
    //         if (WIFEXITED(status))
    //             setup->exit_stat = WEXITSTATUS(status); // >>> to check litter on
//     }
// }

// < should redirect input
// open the file using open() with read permissions.
// redirect stdin to the file using dup2().
// execute the command with execve().
// the file not exitstat (no such file or directory: file.txt) => (exit status with 1)
void    red_input(t_tree *tree, t_setup *setup)
{
	(void)setup;
	(void)tree;
	int		in_file;
	pid_t	pid;
	int		fd[2];
	int		dup_stdin;
	int		status;

	// >>> echo "hello" < text.txt  ======>  print hello
	int i = 0;
	printf("file name -> %s\n", tree->cmd->redirections->file_name);
	printf("tree->cmd->name -> |%s|\n", tree->cmd->name);
	printf("command -> %s\n", tree->cmd->name);
	while (tree->cmd->args[i])
	{
		printf("tree->cmd->args[%d] -> |%s|\n", i, tree->cmd->args[i]);
		i++;
	}
	// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	// in the red_input < the file is read only
	in_file = open(tree->cmd->redirections->file_name, O_RDONLY);
	if (in_file == -1)
		ft_perror(setup, NULL, FAIL);
	if (pipe(fd) == -1)
		ft_perror(setup, NULL, FAIL);
	pid = fork();
	if (pid == -1)
		ft_perror(setup, NULL, FAIL);
	// >>> have first put a backup of the stdin without losing it
	dup_stdin = dup(0);
	// >>>>> | < txt.txt cat | <<<<<
	if (dup2(in_file, 0) == -1)
		ft_perror(setup, NULL, FAIL);


	waitpid(pid, &status, 0);
}
