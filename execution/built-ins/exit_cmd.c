#include "../../srcs/mini_shell.h"

// void	exit_cmd()
// {
// 	// >>> have to free all the allocation here before the exit 
// 	// exit: numeric argument required
// 	// exit: too many arguments" and not exit
// 	if (_arg_len)
// 		exit(0);
// 	else
// 	{
// 		if ();
// 	}

// }

// void cd(t_set_env *built_in)
// {
//     int status;
//     char *home;

//     if (built_in->cmd->args[1] == NULL)
//     {
//         home = getenv("HOME");
//         if (!home)
//         {
//             fprintf(stderr, "cd: 'HOME' not set\n");
//             return;
//         }
//         status = chdir(home);
//         if (status == -1)
//             perror("cd");
//     }
//     else
//     {
//         status = chdir(built_in->cmd->args[1]);
//         if (status == -1)
//             perror("cd");
//     }
// }

// void get_pwd(t_set_env *built_in)
// {
//     char buf_path[PATH_MAX];
//     char *path;

//     path = getcwd(buf_path, sizeof(buf_path));
//     if (path)
//         built_in->pwd = strdup(path);
//     else
//         perror("pwd");
// }

// void cd_cmd(t_set_env *built_in)
// {
//     cd(built_in);
//     free(built_in->pwd);
//     get_pwd(built_in);
// }