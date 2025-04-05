#include "mini_shell.h"

// void	clear_fds(t_setup *setup)
// {
// 	int	i;

// 	i = 0;
// 	while (setup->fds_backups[i])
// 	{
// 		close(setup->fds_backups[i]);
// 		i++;
// 	}
// 	setup->idx_fds = 0;
// }

// void	add_buffer_fds(t_setup	*setup, int	fd)
// {
// 	setup->fds_backups[setup->idx_fds] = fd;
// 	setup->idx_fds++;
// }