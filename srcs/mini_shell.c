#include "mini_shell.h"

// cc cc.c -lreadline -o a.out
int main(int argc, char **argv, char **env)
{
    char *input;
    argv[1] = NULL;
    if (argc == 1)
    {
        while (1)
        {


            input = readline("minishell$ ");
            if (input == NULL)
            {
                free(input);
                printf("minishell exit done\n");
                break;
            }
            
            // >>> parsing (tokenization)
                // will start here.
                // just to take an image.
            // <<<

            cd_cmd(input);

            // echo_cmd(input);
            // pwd_cmd(input);
            // exit_cmd(input);
            env_cmd(input, env);
            free(input);
        }
    }
    else
    {
        printf("RUN './minishell' with no extra args, please ;)\n");
        exit(1);
    }
    return 0;
}

// main for the test leak.
// int main()
// {
//     char *input;

//     input = "pwd";
//     pwd_cmd(input);

// }