# include "mini_shell.h"

// >>> i have here the delimiter
void    heredoc(t_setup *setup)
{
    int     in_file;
    char    *input;

    in_file = open("heredoc.txt", O_CREAT | O_RDWR, 0644);
    if (in_file == -1)
        ft_perror("open: failed\n", FAIL);
    while (1)
    {
        input = readline("heredoc> ");
        if (input == NULL || ft_strcmp(input, setup->cmd->args[0]) == 0) // delimiter)
        {
            close(in_file);
            break;
        }
        write(in_file, input, ft_strlen(input));
        write(in_file, "\n", 1);
    }
    // >>> unlink to remove the heredoc.txt file when finishing
    return ;
}