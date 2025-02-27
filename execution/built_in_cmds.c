#include "../mini_shell/mini_shell.h"

// ft_strncmp(&map[len - 4], ".ber", 4) != 0

// ◦ echo with option -n
void	echo_cmd(char *args)
{
	char	*str;
	size_t	arg_len;

	str = NULL;
	arg_len = ft_strlen(args);
	if (ft_strncmp(&args[5], "-n", 2) == 0) // here a 
	{
		str = ft_strjoin(&args[5], "\n");
		write(1, str, ft_strlen(str));
		free(str);
	}
	else
		write(1, &args[5], ft_strlen(args));
}

// ◦ cd with only a relative or absolute path
// void    cd_cmd()

// ◦ pwd with no options
// ◦ exit with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments