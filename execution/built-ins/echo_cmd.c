#include "../../srcs/mini_shell.h"

void    echo_cmd(char *input)
{
	int		arg_pos;
	int		newline;

	arg_pos = 5;
	newline = 1;
	while (input[arg_pos] == ' ')
        arg_pos++;
	while (input[arg_pos] == '-' && input[arg_pos + 1] == 'n')
    {
		newline = 0;
		arg_pos += 2;
		while (input[arg_pos] == 'n')
			arg_pos++;
		while (input[arg_pos] == ' ')
			arg_pos++;
	}
	input = &input[arg_pos];
    execute_echo(input, newline);
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
