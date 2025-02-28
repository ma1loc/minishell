#include "../srcs/mini_shell.h"

// ◦ echo with option -n && have a prompte back with the new line problem to fix with -n options.
void	echo_cmd(char *input)
{
	char	*str;
	size_t	arg_len;
    
	arg_len = 5;
	str = NULL;
	while (input[arg_len] && input[arg_len] == ' ')
        arg_len++;
	if (ft_strncmp(&input[arg_len], "-n", 2) == 0)
	{
		arg_len += 2;
		while (input[arg_len] && input[arg_len] == ' ')
        	arg_len++;
		write(1, &input[arg_len], ft_strlen(input));
		free(str);
	}
	else
	{
		str = ft_strjoin(&input[arg_len], "\n");
		write(1, str, ft_strlen(str));
		free(str);
	}
}
