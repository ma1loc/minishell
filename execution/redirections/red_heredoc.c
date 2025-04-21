#include "mini_shell.h"

// >>> the heredoc function open an alrady open file to read form it
// >>> here i have to get the last heredoc file to take the input form it


// int	red_heredoc(t_setup *setup, t_tree *tree)
// {
//     int		i;

//     i = setup->i;
//     if (tree->cmd->name == NULL)
//         return (close(setup->heredoc->fd[i]), 1);
//     else
//     {
//         if (dup2(setup->heredoc->fd[i], STDIN_FILENO) == -1)
//         {
//             close(setup->heredoc->fd[i]);
//             return (ft_perror(setup, "Error: dup2 failed\n", EXIT_FAILURE), -1);
//         }
//         close(setup->heredoc->fd[i]);
//     }
// 	setup->i++;
//     return (0);
// }

// void execute_redirections(t_tree *tree, t_setup *setup)
// {
//     t_redirections *redir;
//     int original_stdin = dup(STDIN_FILENO);
//     int original_stdout = dup(STDOUT_FILENO);
//     int redirect_performed = 0;

    
//     redir = tree->cmd->redirections;
//     while (redir)
//     {
//         if (redir->type == TOKEN_HERDOC)
//         {
//             int found = 0;
//             for (int i = 0; i < setup->heredoc_counter; i++)
//             {
//                 if (ft_strcmp(setup->heredoc->delim_map[i], redir->file_name) == 0)
//                 {
//                     int fd = open(setup->heredoc->file_name[i], O_RDONLY);
//                     if (fd >= 0)
//                     {
//                         dup2(fd, STDIN_FILENO);
//                         close(fd);
//                         found = 1;
//                         redirect_performed = 1;
//                         break;
//                     }
//                 }
//             }
//             if (!found)
//             {
//                 ft_perror(setup, "heredoc file not found", EXIT_FAILURE);
//                 return;
//             }
//         }
// 		else if (redir->type == TOKEN_RED_IN)
// 			red_input(setup, tree, redir);
	
// 		else if (redir->type == TOKEN_RED_OUT)
// 			red_output(setup, tree, redir);

// 		else if (redir->type == TOKEN_RED_INOUT)
// 			red_in_out(setup, tree, redir);
// 		else if (redir->type == TOKEN_APPEND)
// 			red_append(setup, tree, redir);
        
// 		break;
//         redir = redir->next;
//     }
    
//     execute_commands(tree, setup);
    
//     if (redirect_performed)
//     {
//         dup2(original_stdin, STDIN_FILENO);
//         dup2(original_stdout, STDOUT_FILENO);
//     }
//     close(original_stdin);
//     close(original_stdout);
// }

// int	red_heredoc(t_setup *setup, t_tree *tree)
// {
// 	(void)tree;
// 	int	i = setup->i;

// 	if (dup2(setup->heredoc->fd[i], STDIN_FILENO) == -1)
// 	{
// 		close(setup->heredoc->fd[i]);
// 		return (ft_perror(setup, "Error: dup2 failed\n", EXIT_FAILURE), -1);
// 	}
// 	// maybe don’t close here if you'll need it again
// 	setup->i++;
// 	return (0);
// }

// int	red_heredoc(t_setup *setup, t_tree *tree, t_redirections *redir)
// {
// 	int found;
// 	int	i;

// 	(void)tree;
// 	i = 0;
// 	found = 0;
//     while (i < setup->heredoc_counter)
//     {
//         if (ft_strcmp(setup->heredoc->delim_map[i], redir->file_name) == 0)
//         {
//             int fd = open(setup->heredoc->file_name[i], O_RDONLY);
//                 if (fd >= 0)
//                 {
//                     dup2(fd, STDIN_FILENO);
//                     close(fd);
//                     found = 1;
//                     break;
//                 }
//             }
//         }
//     if (!found)
//     {
//         ft_perror(setup, "heredoc file not found", EXIT_FAILURE);
// 		return (1);
// 	}
// 	return (0);
// }


int red_heredoc(t_setup *setup, t_tree *tree, t_redirections *redir)
{
    int found;
    int i;

    (void)tree;
    i = 0;
    found = 0;
    while (i < setup->heredoc_counter)
    {
        if (ft_strcmp(setup->heredoc->delim_map[i], redir->file_name) == 0)
        {
            int fd = open(setup->heredoc->file_name[i], O_RDONLY);
            if (fd >= 0)
            {
                dup2(fd, STDIN_FILENO);
                close(fd);
                found = 1;
                break;
            }
        }
        i++; // This increment was missing, causing infinite loop
    }
    if (!found)
    {
        ft_perror(setup, "heredoc file not found", EXIT_FAILURE);
        return (1);
    }
    return (0);
}