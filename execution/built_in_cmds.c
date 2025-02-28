#include "../mini_shell/mini_shell.h"

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


// ◦ cd with only a relative or absolute path
// chdir() is a syscall use to change the location of the current path
// like [cd ..] [cd example.txt]
void    cd_cmd(char *input)
{
	int		i;

	if (!input || *input)
		getenv("HOME");
	i = 0;
	while (input[i] && input[i] == ' ')
		i++;
	if (ft_strncmp(&input[i], "cd", 2) == 0)
	{
		input = &input[i + 2];
		i = 0;
		while (input[i] && input[i] == ' ')
			i++;
		if (chdir(&input[i]) == -1)
			perror("cd");
	}
}


// ◦ pwd with no options
// getcwd is a func (not syscall!!!) that get the current path your in.
void	pwd_cmd(char *input)
{
	char	path[1024];
	char	*pwd;

	pwd = NULL;
	if (ft_strncmp(input, "pwd", 3) == 0)
	{
		pwd = getcwd(path, sizeof(path));
		if (pwd)
		{
			pwd = ft_strjoin(path, "\n");
			ft_putstr_fd(pwd, 1);
			free(pwd);
		}
		else
			perror("pwd:");
    }
}


// ◦ exit with no options
void	exit_cmd(char *input)
{
	if (ft_strncmp(input, "exit", 4) == 0)
		exit(0);
}

// ◦ export with no options

// ◦ unset with no options

// ◦ env with no options or arguments