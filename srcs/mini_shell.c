#include "mini_shell.h"

int main(int argc, char **argv, char **env)
{
    (void)argv;
    char    *input;
    t_env   *set_env;

    input = NULL;
    set_env = init_env(env);
    if (argc == 1)
    {
<<<<<<< HEAD
=======
        signal(SIGINT, signals); // 'ctrl + c'
        signal(SIGQUIT, signals); // 'ctrl + \' // >>> (does nothing fix).
        // char *args[] = {input, NULL };
>>>>>>> 4b13520 (update)
        while (1)
        {
            input = readline("minishell$ "); // prompt && take input 
            if (input == NULL)
                break;

<<<<<<< HEAD
=======
            // >>> parsing (tokenization)
                // will start here.
                // just to take an image.
            // <<<

>>>>>>> 4b13520 (update)
            // >>> build-ins.
            if (ft_strncmp(input, "echo", 4) == 0)
                echo_cmd(input);
            if (ft_strncmp(input, "cd", 2) == 0)
                cd_cmd(input);
            if (ft_strncmp(input, "pwd", 3) == 0)
                pwd_cmd(input);
            if (ft_strncmp(input, "exit", 4) == 0)
                exit_cmd();    
            if (ft_strncmp(input, "env", 3) == 0)
<<<<<<< HEAD
                env_cmd(set_env);
            if (ft_strncmp(input, "unset", 5) == 0)
            {
                char **inp = ft_split(input, ' ');
                if (inp[1] == NULL)
                    printf("few unset args !!!\n");
                else
                    unset_cmd(&set_env, inp[1]);
            }
=======
                env_cmd(env);
>>>>>>> 4b13520 (update)
        }
    }
    else
    {
        printf("RUN './minishell' with no extra args, please ;)\n");
        exit(1);
    }
    return 0;
}

<<<<<<< HEAD
=======


            // env_cmd(input, env);
            // pwd_cmd(input);
            // cd_cmd(input);
            // exit_cmd(input);
            
            // here >>> add the input from the readline in the history buffer
            // check for not include the enter lines in the history (just valid input)
            // add_history(input); allocates memory for storing the command
            // if (input && *input)
            //     add_history(input);
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
            // free(input);
            // exit(111);
        // }
>>>>>>> 4b13520 (update)
