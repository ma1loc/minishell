#include "../../srcs/mini_shell.h"

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
{
	// >>> have to free all the allocation here before the exit 
	// exit: numeric argument required
	// exit: too many arguments" and not exit
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
}