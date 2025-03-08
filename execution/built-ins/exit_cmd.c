#include "../../srcs/mini_shell.h"

<<<<<<< HEAD
void	exit_cmd(t_set_env  *built_in)
=======
// exit with no options
<<<<<<< HEAD
int		arg_len(char **arg)
{
	int	len;

	len = 0;
	while (arg[len])
		len++;
}

void	exit_cmd()
>>>>>>> 0ce570e13e4b0b223063194c26e845647d18e9d8
{
	// >>> have to free all the allocation here before the exit 
	// exit: numeric argument required
	// exit: too many arguments" and not exit
<<<<<<< HEAD
	
    // if (built_in->cmd->args[1])
	// 	exit(0);
    // else
    printf("%s", built_in->cmd->args[0]);

=======
	int	_arg_len;

	_arg_len = arg_len(arg);
	if (_arg_len >= 1)
		exit(0);
	else
	{
		if ();
	}

=======
void	exit_cmd()
{
	// >>> have to free all the allocation here before the exit 
	exit(0);
>>>>>>> 4b13520 (update)
>>>>>>> 0ce570e13e4b0b223063194c26e845647d18e9d8
}