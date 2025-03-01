#include "../srcs/mini_shell.h"

void handle_sigint(int sig)
{
    if (sig == SIGINT)
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
}
