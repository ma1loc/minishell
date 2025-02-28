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
            
            // >>> parsing
                // will start here.
                // just to take an image.
            // <<<


	        // printf(">>> %s\n", input);
	        // printf(">>>%s\n", &input[5]);

            // char cwd[1024];
            // if (ft_strncmp(input, "pwd", 3) == 0)
            // {
            //     getcwd(cwd, sizeof(cwd));
            //     printf("%s\n", cwd);
            // }
            
            // echo_cmd(input);
            // pwd_cmd(input);
            // cd_cmd(input);
            // exit_cmd(input);
            env_cmd(input, env);
            // printf("%s\n", getenv(input));
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