#include "mini_shell.h"

// int main(int argc, char **argv, char **env)
int main(int argc, char **argv, char **env)
{
    char *input;
    argv[1] = NULL;

    input = NULL;
    if (argc == 1)
    {
        signal(SIGINT, signals); // 'ctrl + c'
        signal(SIGQUIT, signals); // 'ctrl + \' // >>> (does nothing fix).
        while (1)
        {
            input = readline("minishell$ "); // prompt && take input 
            if (input == NULL)
                break;

            // >>> parsing (tokenization)
                // will start here.
                // just to take an image.
            // <<<

            // >>> just a command to test.
            env_cmd(input, env);
            echo_cmd(input);
            pwd_cmd(input);
            cd_cmd(input);
            exit_cmd(input);
            
            // here >>> add the input from the readline in the history buffer
            // check for not include the enter lines in the history (just valid input)
            // add_history(input); allocates memory for storing the command
            if (input && *input)
                add_history(input);
			// rl_clear_history();

			// test
			// t_env *done_env;
			// done_env = env_split(env);
			// while (done_env)
			// {
			// 	printf("%s", done_env->key);
			// 	printf("=");
			// 	printf("%s", done_env->value);
			// 	done_env = done_env->next;
			// }

            free(input);
            // exit(111);
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


// int main() {
//     signal(SIGQUIT, do_nothing);

//     while (1) {
//         write(1, "minishell$ ", 11);
//         sleep(1);
//     }

//     return 0;
// }
