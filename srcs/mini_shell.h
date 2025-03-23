# ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include "../parsing/tokenizer.h"

# define PATH_MAX 4096

// >>> exit status define
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define SYNTAX_ERROR 2
# define CMD_NOT_FOUND 127
# define CMD_NOT_EXEC 126
// # define EXIT_SEVERE 128
// # define EXIT_SEVERE 130 for the ctrl + c (heredoc case)
// >>>>>>>>>>>>>>>>>>>>>>>

// >>> define the built_in and external cmd
# define BUILT_IN 1
# define EXTERNAL 0

// >>> true or false (readable)
#define true	1
#define false	0

// >>> libft
size_t	ft_strlen(char *str);
char	**ft_split(char *str, char separator);
char	*ft_strjoin(char *s1, char *s2);
int     ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strdup(char *s1);
void	ft_putstr_fd(char *s, int fd);
int     ft_strcmp(char *s1, char *s2);
void	*ft_memset(void *str, int c, size_t n);
int     ft_isdigit(char *str);
int     ft_atoi(const char *str);
char	*ft_strchr(char *s, int c);

// >>> sig
// void	signals(int signal);
// void	do_sigint();
// void	do_sigquit();

// >>> export && unset

// >>> struct for the env variables

typedef struct s_env
{
    char    *key;
    char    *value;
    struct  s_env *next;
}   t_env;

t_env	*ft_lstlast(t_env *lst);
void	ft_lstadd_back(t_env **lst, t_env *new);

// >>> start init all the env
typedef struct s_setup
{
    char        *input;
    t_env       *env;
    t_token     *token;
    t_command   *cmd;
    t_tree      *tree;
    char        *pwd;
    char        *oldpwd;
    char        *cmd_path;
    char        **env_list;
    char        **envp;
    int         exit_stat;
}   t_setup;

// >>>>>>>>>>>>>>>>>>>> built_in_cmds <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void    echo_cmd(t_setup *built_in);       // the echo command fun. [done]
void    cd_cmd(t_setup *built_in);         // the cd command fun. [done]
void	pwd_cmd(t_setup *built_in);        // the pwd path print fun. [done]
void	get_pwd(t_setup *built_in);
t_env	*init_env(char **env, t_env *env_list);
void	env_cmd(t_setup *built_in);
void	unset_cmd(t_env **env_list, char *key);
// void    unset_cmd(t_setup *setup, char *key);
void	set_env(t_env **env_list, char *key, char *value);
void    cd(t_setup *built_in);
void	exit_cmd(t_setup  *built_in);
void	export_cmd(t_setup	*built_in);

// >>> hellping functions
void    ft_perror(t_setup *setup, char *msg, int exit_stat);
void	free_spliting(char **split_path);

// >>> the execution will start here
int     command_type(char *name);
int     is_built_in(char *name);
t_setup *shell_env_setup(char **env);
t_setup *init_setup_struct();
void    heredoc(t_tree *tree, t_setup *setup);
char	*path_resolver(t_setup *setup);
char	*split_path(char *path, char *cmd);

// >>>>>>>>>>>>>>>>> execution >>>>>>>>>>>>>>>>>>>>
void    execution(t_tree *tree, t_setup *setup);
void	execute_internal(t_command *cmd, t_setup *setup);
void    execute_command(t_tree *tree, t_setup *setup);
void    execute_pipe(t_tree *tree, t_setup *setup);

// >>>>>>>>>>>>>>>> redirections >>>>>>>>>>>>>>>>>>
// void	handle_redirections(t_tree *tree, t_setup *setup);
void	redirections_and_execute(t_tree *tree, t_setup *setup);
void	heredoc(t_tree *tree, t_setup *setup);
// void	red_input(t_tree *tree, t_setup *setup);
// void	red_output(t_tree *tree, t_setup *setup);
// int		red_input(t_tree *tree, t_setup *setup);
// int		red_output(t_tree *tree, t_setup *setup);
void	red_append(t_tree *tree, t_setup *setup);



// void execute_tree(t_tree *root);
// void	env_cmd(t_env *env_list);

// >>> env command

// // >>> unset command

# endif