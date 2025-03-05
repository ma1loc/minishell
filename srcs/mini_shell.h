# ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>

// # define PATH_MAX 1024

// >>> libft
size_t	ft_strlen(char *str);
char	**ft_split(char *str, char separator);
char	*ft_strjoin(char *s1, char *s2);
int     ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strdup(char *s1);
void	ft_putstr_fd(char *s, int fd);
int     ft_strcmp(char *s1, char *s2);

// >>> built_in_cmds
void	echo_cmd(char *input);              // the echo command fun. [done]
void    execute_echo(char *input, int newline);
int     cd_cmd(char *args);                 // the cd command fun. [done]
void	pwd_cmd();                          // the pwd path print fun. [done]
void	exit_cmd();              // the exit command fun.

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
} t_env;

t_env   *init_env(char **env);
void    print_env(t_env *env_list);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstadd_back(t_env **lst, t_env *new);
void	unset_env(t_env **env_list, char *key);
void	env_cmd(char **env);


# endif