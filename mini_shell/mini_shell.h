# ifndef MINI_SHELL_C
# define MINI_SHELL_C

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define HELLO "hello"

// >>> libft
size_t  ft_strlen(char *str);
char	**ft_split(char *str, char separator);
char	*ft_strjoin(char *s1, char *s2);
int	    ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strdup(char *s1);
void	ft_putstr_fd(char *s, int fd);

// >>> built_in_cmds
void    echo_cmd(char *args);   // the echo command fun.
void	pwd_cmd(char *input);   // the pwd path print fun.
// void    cd_cmd(char *args);

# endif