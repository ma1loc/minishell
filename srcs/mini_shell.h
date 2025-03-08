# ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "../parsing/tokenizer.h"

# define PATH_MAX 4096

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
int     ft_strcmp(char *s1, char *s2);
int     ft_isnum(int c);


<<<<<<< HEAD
=======
// >>> built_in_cmds
void	echo_cmd(char *input);              // the echo command fun. [done]
void    execute_echo(char *input, int newline);
int     cd_cmd(char *args);                 // the cd command fun. [done]

void	pwd_cmd();               // the pwd path print fun.

// void	exit_cmd(char *input);              // the exit command fun.
// void	env_cmd(char *input, char **env);   // the env command fun.
void	pwd_cmd();                          // the pwd path print fun. [done]
void	exit_cmd();              // the exit command fun.

>>>>>>> 0ce570e13e4b0b223063194c26e845647d18e9d8
// >>> sig
void	signals(int signal);
void	do_sigint();
void	do_sigquit();

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
typedef struct s_set_env
{
    char        *input;
    t_env       *env;
    t_token     *token;
    t_command   *cmd;
    char        *pwd;
    char        *oldpwd;
    char        **env_split;
    t_env       *env_list;
}   t_set_env;

// >>> built_in_cmds
void    echo_cmd(t_set_env *built_in);       // the echo command fun. [done]
void    cd_cmd(t_set_env *built_in);         // the cd command fun. [done]
void	pwd_cmd(t_set_env *built_in);        // the pwd path print fun. [done]
void	get_pwd(t_set_env *built_in);
t_env	*init_env(char **env, t_set_env *set_env);
void	env_cmd(t_set_env *built_in);
void	unset_cmd(t_env **env_list, char *key);
void	set_env(t_env **env_list, char *key, char *value);
void	get_oldpwd(t_set_env *built_in);
void	exit_cmd(t_set_env  *built_in);

// void	env_cmd(t_env *env_list);

// >>> env command

// // >>> unset command

<<<<<<< HEAD
t_env	*ft_lstlast(t_env *lst);
void	ft_lstadd_back(t_env **lst, t_env *new);

// >>> built_in_cmds
void	echo_cmd(char *input);              // the echo command fun. [done]
void    execute_echo(char *input, int newline);
int     cd_cmd(char *args);                 // the cd command fun. [done]
void	pwd_cmd();                          // the pwd path print fun. [done]
void	exit_cmd();              // the exit command fun.

// >>> env command
t_env   *init_env(char **env);
void	env_cmd(t_env *env_list);

// >>> unset command
void	unset_cmd(t_env **env_list, char *key);
=======
t_env   *init_env(char **env);
void    print_env(t_env *env_list);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstadd_back(t_env **lst, t_env *new);
void	unset_env(t_env **env_list, char *key);
void	env_cmd(char **env);

>>>>>>> 4b13520 (update)

# endif