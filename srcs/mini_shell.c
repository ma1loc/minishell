#include "mini_shell.h"

// int main(int argc, char **argv, char **env)
int main(int argc, char **argv)
{
    char *input;
    argv[1] = NULL;

    input = NULL;
    if (argc == 1)
    {
        // signal(SIGINT, handle_sigint);
        while (1)
        {
            input = readline("minishell$ "); // prompt && take input 
            if (input == NULL)
            {
                // free(input);
                printf("minishell exit done\n");
                break;
            }
            // >>> parsing (tokenization)
                // will start here.
                // just to take an image.
            // <<<

            // >>> just a command to test.
            // env_cmd(input, env);
            
            // exit_cmd(input);
            // here >>> add the input from the readline in the history buffer
            // check for not include the enter lines in the history (just valid input)
            // add_history(input); allocates memory for storing the command
            if (input && *input)
                add_history(input);
            exit(100);
            // rl_clear_history();
            // free(input);
        }
    }
    else
    {
        printf("RUN './minishell' with no extra args, please ;)\n");
        exit(1);
    }
    return 0;
}

// enum    token_numbers
// {
//     NUM1,
//     NUM2,
//     NUM3,
//     NUM4,
//     NUM5
// };

// int main()
// {
//     printf("%d", NUM1);
// }
