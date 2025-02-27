#include "../mini_shell/mini_shell.h"


// ◦ echo with option -n
void	echo_cmd(char *args)
{
	char	*str;
	size_t	arg_len;

	str = NULL;
	arg_len = ft_strlen(args);
	if (ft_strncmp(args, "-n", 2) == 0) // here a 
	{
		str = ft_strjoin(args, "\n");
		write(1, str, ft_strlen(str));
		free(str);
	}
	else
		write(1, args, ft_strlen(args));
}

// ◦ cd with only a relative or absolute path
// void    cd_cmd()

// ◦ pwd with no options
// ◦ exit with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments