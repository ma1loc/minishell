#include "mini_shell.h"

void	execute_redirections(t_tree *tree, t_setup *setup)
{
	int				status;
    int				save_stdin;
    int				save_stdout;
    t_redirections	*current;

	status = 0;
	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
    current = tree->cmd->redirections;
    while (current != NULL)
    {
        if (current->type == TOKEN_RED_IN)
            status = red_input(setup, tree, current);
        else if (current->type == TOKEN_RED_OUT)
			status = red_output(setup, tree, current);
		else if (current->type == TOKEN_RED_INOUT)
			status = red_in_out(setup, tree, current);
		else if (current->type == TOKEN_APPEND)
			status = red_append(setup, tree, current);
		else if (current->type == TOKEN_HERDOC)
			status = red_heredoc(setup, tree);
		if (status == -1)
			break;
		current = current->next;
    }
	if (status == -1)
	{
		dup2(save_stdin, STDIN_FILENO);
    	dup2(save_stdout, STDOUT_FILENO);
    	close(save_stdin);
    	close(save_stdout);
		return ;
	}
	if (status == 0)
		execute_commands(tree, setup);
    dup2(save_stdin, STDIN_FILENO);
    dup2(save_stdout, STDOUT_FILENO);
    close(save_stdin);
    close(save_stdout);
}


// void	execute_redirections(t_tree *tree, t_setup *setup)
// {
// 	int status;
//     int save_stdin;
//     int save_stdout;
//     t_redirections *current;

// 	// result = -1;
// 	status = 0;
// 	save_stdin = dup(STDIN_FILENO);
// 	save_stdout = dup(STDOUT_FILENO);
//     current = tree->cmd->redirections;
//     while (current != NULL)
//     {
// 		if (current->type == TOKEN_RED_IN)
// 	        status = red_input(setup, tree, current);
//     	else if (current->type == TOKEN_RED_OUT)
// 			status = red_output(setup, tree, current);
// 		else if (current->type == TOKEN_RED_INOUT)
// 				status = red_in_out(setup, tree, current);
// 		else if (current->type == TOKEN_APPEND)
// 			status = red_append(setup, tree, current);
// 		else if (current->type == TOKEN_HERDOC)
// 				status = red_heredoc(setup, tree);
// 		if (status == -1)
// 				break;
// 		current = current->next;
//     }
// 	if (status != -1)
// 		execute_commands(tree, setup);
//     dup2(save_stdin, STDIN_FILENO);
//     dup2(save_stdout, STDOUT_FILENO);
//     close(save_stdin);
//     close(save_stdout);
// }
