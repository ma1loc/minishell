# include "mini_shell.h"

// >>> signal handler here to
void    heredoc(t_tree *tree, t_setup *setup)
{
    int     in_file;
    char    *input;

    in_file = open("heredoc.txt", O_CREAT | O_RDWR, 0644);
    if (in_file == -1)
        ft_perror(setup, "Error: open failed\n", FAIL);
    while (true)
    {
        input = readline("heredoc> ");
<<<<<<< HEAD
        if (input == NULL || ft_strcmp(input, tree->cmd->redirections->file_name) == 0) // >>> delimiter check
=======
        if (input == NULL || ft_strcmp(input, setup->cmd->redirections->file_name) == 0) // >>> delimiter check
>>>>>>> 45b042e (update the and fix some stuff)
        {
            
            close(in_file);
            break;
        }
        write(in_file, input, ft_strlen(input));
        write(in_file, "\n", 1);
    }
    execute_command(tree, setup);   // >>> to check litter on
    // >>> unlink to remove the heredoc.txt file when finishing, to do litter
    unlink("/home/yanflous/Desktop/minishell/heredoc.txt");
    return ;
}
// recursive descent parsing
