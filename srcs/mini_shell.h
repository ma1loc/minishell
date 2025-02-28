# ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define HELLO "hello"

// >>> libft
size_t  ft_strlen(char *str);
char	**ft_split(char *str, char separator);
char	*ft_strjoin(char *s1, char *s2);
int     ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strdup(char *s1);
void	ft_putstr_fd(char *s, int fd);

// >>> printf
int ft_printf(const char *s, ...);
int ft_putchar(char c);
int	ft_putstr(char *s);
int	ft_putnbr(int n);
int	ft_puthex(unsigned int un, char c);
int	ft_putuint(unsigned int un);
int	ft_putadd(void *add);

// >>> built_in_cmds
void	echo_cmd(char *input);               // the echo command fun.
void    cd_cmd(char *args);                 // the cd command fun.
void	pwd_cmd(char *input);               // the pwd path print fun.
void	exit_cmd(char *input);              // the exit command fun.
void	env_cmd(char *input, char **env);   // the env command fun.    

typedef struct s_tokenization
{
    char    *command;
    char    *argument;
    char    *redirection;
    char    *filename;
}   t_tokenization;

# endif