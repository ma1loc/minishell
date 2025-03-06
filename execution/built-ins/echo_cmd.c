#include "../../srcs/mini_shell.h"

// >>> echo -nnnnnnnnnnnnnnnnnnnnnnnnnnnnngnn hellllllloo your loser >>> to fix
void    echo_cmd(char *input)
{
	int		arg_pos;
    int     save_start;

	arg_pos = 5;
	while (input[arg_pos] == ' ')
        arg_pos++;
	while (input[arg_pos] == '-' && input[arg_pos + 1] == 'n')
    {
        save_start = arg_pos;
		arg_pos += 2;
        while (input[arg_pos])
        {
		    if (input[arg_pos] == 'n' || input[arg_pos + 1] == ' ')
			    arg_pos++;
            else
            {
                execute_echo(&input[save_start], 0);
                return ;
            }
        }
	}
	input = &input[arg_pos];
    execute_echo(input, 1);
}

void    execute_echo(char *input, int newline)
{
	int		i;

	i = 0;
    while (input[i] == ' ')
        i++;
    int prev_space = 0;
    while (input[i])
    {
        if (input[i] == ' ')
        {
            if (!prev_space)
                write(1, " ", 1);
            prev_space = 1;
        }
        else
        {
            write(1, &input[i], 1);
            prev_space = 0;
        }
        i++;
    }
    if (newline)
        write(1, "\n", 1);
}
