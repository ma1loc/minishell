# include "mini_shell.h"

void    heredoc(t_setup *setup)
{
    int     in_file;
    char    *input;

    in_file = open("heredoc.txt", O_CREAT | O_RDWR, 0644);
    if (in_file == -1)
        ft_perror("open: failed\n", FAIL);
    while (true)
    {
        input = readline("heredoc> ");
        if (input == NULL || ft_strcmp(input, setup->cmd->redirections->file_name) == 0) // delimiter)
        {
            close(in_file);
            break;
        }
        write(in_file, input, ft_strlen(input));
        write(in_file, "\n", 1);
    }
    // >>> unlink to remove the heredoc.txt file when finishing, to do litter
    return ;
}
// recursive descent parsing
