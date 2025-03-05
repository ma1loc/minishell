#include "../../srcs/mini_shell.h"

// exit with no options
void	exit_cmd()
{
	// >>> have to free all the allocation here before the exit 
	exit(0);
}