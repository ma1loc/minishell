// # include "mini_shell.h"

// void	get_heredoc_fds(t_tree *tree, t_setup *setup)
// {
// 	char	*file_num;
// 	char	*file_name;
// 	int		count;
// 	char	*input;
	
// 	count = setup->heredoc->count;
// 	file_num = ft_itoa(count);
// 	file_name = ft_strjoin("/tmp/heredoc", file_num);

// 	setup->heredoc->fd[count] = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
// 	if (!setup->heredoc->fd[count])
// 		return ;
	
// 	while (true)
// 	{
// 		input = readline("heredoc> ");
// 		if (input == NULL || ft_strcmp(input, tree->cmd->redirections->file_name) == 0)
// 		{
// 			free(input);
// 			break;
// 		}
// 		write(setup->heredoc->fd[setup->i], input, ft_strlen(input));
// 		write(setup->heredoc->fd[setup->i], "\n", 1);
// 		free(input);
// 	}

// 	close(setup->heredoc->fd[count]);
// 	setup->heredoc->fd[count] = open(file_name, O_RDONLY, 0644);
// 	if (!setup->heredoc->fd[count])
// 		return ;
// 	free(file_num);
// 	free(file_name);
// }

// void	get_heredoc_count(t_tree *tree, t_setup *setup)
// {
// 	if (!tree)
//         return ;

//     if (tree->cmd && tree->cmd->redirections)
//     {
//         t_redirections *redir = tree->cmd->redirections;
//         while (redir)
//         {
//             if (redir->type == TOKEN_HERDOC)
// 			{
//                 get_heredoc_fds(tree, setup);
// 				setup->i++;
// 				setup->heredoc->count++;
// 			}
//             redir = redir->next;
//         }
//     }
//     get_heredoc_count(tree->left, setup);
//     get_heredoc_count(tree->right, setup);
// }

// void	process_heredoc(t_tree *tree, t_setup *setup)
// {
// 	setup->heredoc->count = 0;
// 	get_heredoc_count(tree, setup);
// }


