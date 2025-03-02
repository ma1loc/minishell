# ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

// >>> libft
size_t	ft_strlen(char *str);
char	**ft_split(char *str, char separator);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strdup(char *s1);
void	ft_putstr_fd(char *s, int fd);

// >>> built_in_cmds
void	echo_cmd(char *input);               // the echo command fun.
void	cd_cmd(char *args);                 // the cd command fun.
void	pwd_cmd(char *input);               // the pwd path print fun.
void	exit_cmd(char *input);              // the exit command fun.
void	env_cmd(char *input, char **env);   // the env command fun. 

// >>> export && unset
// >>> struct for the env variables
typedef struct s_env
{
    char    *key;
    char    *value;
    struct  s_env *next;
} t_env;

int		env_len(char **env);
t_env	*env_split(char	**env);

// >>> sig
void	signals(int signal);
void	do_sigint();
void	do_sigquit();


# endif