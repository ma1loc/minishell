# include "mini_shell.h"

void	allocation_failed_msg()
{
	ft_putstr_fd("minishell: Error: memory "\
		"allocation failed.\n", STDERR_FILENO);
	gc_destroy(g_gc);
	exit(EXIT_FAILURE);
}

// maximum here-document count exceeded
void	maximum_heredoc_msg()
{
	ft_putstr_fd("minishell: maximum here-document "\
		"count exceeded.\n", STDERR_FILENO);
	gc_destroy(g_gc);
	exit(SYNTAX_ERROR);
}

void	do_eof_heredoc(t_setup *setup)
{
	// (void)setup;
	// i think here i have to clean up the heredoc things
	ft_putstr_fd("minishell: warning: here-document "\
		"delimited by end-of-file.\n", STDERR_FILENO);	
	cleanup_heredoc(setup);
	exit(EXIT_SUCCESS);
}

// void	