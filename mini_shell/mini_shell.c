#include "mini_shell.h"

// cc cc.c -lreadline -o a.out
int main(int argc, char **argv)
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
            
            // >>> parsing
                // will start here.
                // just to take an image.
            // <<<


	        // printf(">>> %s\n", input);
	        printf(">>> %s\n", &input[5]);
            // echo_cmd(input);
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
