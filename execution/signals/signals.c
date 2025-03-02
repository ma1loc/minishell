#include "../../srcs/mini_shell.h"

// Do-do signals
// >>> ctrl + d >>> exit

// >>> ctrl + c >>> new_prompte (SIGINT)
void	do_sigint()
{
	// Resets Readline for a fresh input line (what ever if you 
	// write some thing like -> minishell$ hello^C will go new line)
	rl_on_new_line();
	// Replaces the user's current input line 
	// (The input for example "ls -l" is cleared, and the prompt is refreshed)
	rl_replace_line("", 1); // why 0 - 1 ???
	// Refreshes the input display
	rl_redisplay();
	printf("\nminishell$ ");
}

void do_sigquit()
{
	printf("\nminishell$ ");
}

// >>> main func.
void	signals(int signal)
{
	if (signal == SIGINT)
		do_sigint();
	if (signal == SIGQUIT)
		do_sigquit();
}