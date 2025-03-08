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
	if (opt[i] != '-')
		return (1);
	else
		i++;
	while (opt[i])
	{
		if (opt[i] == 'n')
			i++;
		else
			return (1);
	}
	return (0);
}

void	echo_print(t_command *cmd, int i)
{
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1] != NULL)
			printf(" ");
		i++;
	}
}

void    echo_cmd(t_set_env *built_in)
{
	int	i;

	i = 1;
	if (!built_in->cmd->args[1])
		printf("\n");
	else if (is_option(built_in->cmd->args[i]) == 0)
	{
		i = 2;
		echo_print(built_in->cmd, i);
	}
	else
	{
		echo_print(built_in->cmd, i);
		printf("\n");
	}
}
