# include "mini_shell.h"

void	allocation_failed_msg(t_gc *gc)
{
	ft_putstr_fd("Error: memory allocation failed\n", STDERR_FILENO);
	gc_destroy(gc);
	exit(1);
}
