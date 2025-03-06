# include "mini_shell.h"
# include "../parsing/tokenizer.h"

int main(int argc, char **argv, char **env)
{
    (void)argv;
    char    *input;
    t_env   *set_env;

    input = NULL;
    set_env = init_env(env);
    if (argc == 1)
    {
        while (1)
        {
            input = readline("minishell$ "); // prompt && take input 
            if (input == NULL)
                break;
            // parser

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
                env_cmd(set_env);
            if (ft_strncmp(input, "unset", 5) == 0)
            {
                char **inp = ft_split(input, ' ');
                if (inp[1] == NULL)
                    printf("few unset args !!!\n");
                else
                    unset_cmd(&set_env, inp[1]);
            }
        }
    }
    else
    {
        printf("RUN './minishell' with no extra args, please ;)\n");
        exit(1);
    }
    return 0;
}

