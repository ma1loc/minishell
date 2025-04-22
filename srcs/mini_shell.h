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
# define HERE_DOC_MAX 16

// >>> to remove litter on
typedef struct s_token t_token;
typedef struct s_command t_command;
typedef struct s_tree t_tree;
typedef struct s_redirections t_redirections;
typedef struct s_expand t_expand;

// >>> exit status define
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define SYNTAX_ERROR 2
# define CMD_NOT_FOUND 127
# define CMD_NOT_EXEC 126
# define EXIT_SEGINT 130
# define EXIT_QUIT 131
// # define EXIT_SEVERE 128
// >>>>>>>>>>>>>>>>>>>>>>>

// >>> define the built_in and external cmd
# define EQUAL 1
# define APPEND 2

// >>> true or false (readable)
#define true	1
#define false	0


typedef struct s_mem
{
	void	*ptr;
	struct	s_mem *next;
}	t_mem;

typedef struct s_gc
{
	t_mem	*mem_list;
	int		total_allocs;
	size_t	total_bytes;
}	t_gc;

extern t_gc *g_gc;


// >>> libft
size_t	ft_strlen(char *str);
char	**ft_split(char *str, char separator);
int     ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);
void	ft_putstr_fd(char *s, int fd);
int     ft_strcmp(char *s1, char *s2);
void	*ft_memset(void *s, int c, size_t len);
char	*ft_substr(char *s1, size_t start, size_t len);
int     ft_isdigit(char *str);
char	*ft_strnstr(char *str, char *to_find, size_t n);
char	*ft_strchr(char *s, int c);
char	*ft_itoa(int n);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstadd_back(t_env **lst, t_env *new);
int		ft_atoi(char *str);

typedef struct s_env
{
	char    *key;
    char    *value;
    struct  s_env *next;
}   t_env;


typedef struct s_heredoc
{
	char	*delimiter;
	int		fd[HERE_DOC_MAX];   // >>> store heredoc pipe fds (read ends)
	char	*file_name[HERE_DOC_MAX];	// >>> sotre file name to unlink them later
	int		qoutes_type;
	char    *delim_map[HERE_DOC_MAX];
}	t_heredoc;


// >>> start init all the env
typedef struct s_setup
{
	int			i;
    char        *input;
    t_env       *env;
    t_token     *token;
    t_command   *cmd;
    t_tree      *tree;
    char        *pwd;
    char        *oldpwd;
    char        *cmd_path;
    char        **envp;
	char		**exec_env;	// >>> for the execve();
    int         exit_stat;
	t_heredoc	*heredoc;
	int			heredoc_flag;
	int			fork_flag;
	int			heredoc_counter;
	// int			seg_heredoc_flag;
}   t_setup;

typedef enum e_export_type
{
	KEY_ONLY,
	ASSIGN_VALUE,
	APPEND_VALUE
}	t_export_type;


// >>>>>>>>>>>>>>>>>>>> built_in_cmds <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void    cd_cmd(t_setup *setup);         // the cd command fun. [done]
void	pwd_cmd(t_setup *setup);        // the pwd path print fun. [done]
int		get_pwd(t_setup *setup);
void    echo_cmd(t_setup *setup);       // the echo command fun. [done]
t_env	*init_env(char **env, t_env *env_list);
void	env_cmd(t_setup *setup);
void	unset_cmd(t_setup *setup);
int		cd(t_setup *setup);
void	exit_cmd(t_setup  *setup);
void	export_cmd(t_setup *setup);
t_export_type	get_export_type(char *arg);
void	export_display(t_setup *setup);
int		export_key_only(t_setup *setup, char *key);
void	update_env(t_setup *setup, char *key, char *value);
void	append_to_env(t_setup *setup, char *key, char *value);
t_env	*get_env_key(t_setup *setup, char *key);


// >>> hellping functions
void	ft_perror(t_setup *setup, char *msg, int exit_stat);
int		is_valid_identifier(char *key);
int		is_valid_number(char *str);
char	*char_to_str(char c);
void	allocation_failed_msg();
void	setup_interactive_signals(void);


// >>>>>>>>>>>>>>>>>>>>>>> gc >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
t_gc	*gc_init();
void	*gc_malloc(t_gc *gc, size_t size);
void	gc_cleanup(t_gc *gc);
void	gc_destroy(t_gc *gc);
void	gc_print_stats(t_gc *gc);	// >>> to remove later on
void	gc_free(t_gc *gc, void *ptr);

// >>>>>>>>>>>>>>>>>>> parsing >>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int		check_space(char *str);


// >>> the execution will start here
t_setup	*start_setup(int argc, char **argv, char **env);
int     is_built_in(char *name);
t_setup *shell_env_setup(char **env);
t_setup *init_setup_struct();
char	*path_resolver(t_setup *setup);
char    **update_exec_envp(t_setup *setup);


// >>>>>>>>>>>>>>>>> execution >>>>>>>>>>>>>>>>>>>>
// void    execution(t_tree *tree, t_setup *setup);
void	execution(t_tree *tree, t_setup *setup);
void	execute_internals(t_command *cmd, t_setup *setup);
void	execute_commands(t_tree *tree, t_setup *setup);
void    execute_pipes(t_tree *tree, t_setup *setup);
void    set_pipe(t_setup *setup, int *fd);
pid_t	set_first_fork(t_setup  *setup, int *fd);
pid_t	set_second_fork(t_setup  *setup, pid_t pid_1, int *fd);
pid_t	set_fork(t_setup *setup);


// >>>>>>>>>>>>>>>> redirections >>>>>>>>>>>>>>>>>>
void	execute_redirections(t_tree *tree, t_setup *setup);
int		red_input(t_setup *setup,t_tree *tree, t_redirections *redirection);
int		red_append(t_setup *setup, t_tree *tree, t_redirections *redirection);
int		red_output(t_setup *setup, t_tree *tree, t_redirections *redirection);
int		red_in_out(t_setup *setup,t_tree *tree, t_redirections *redirection);
int		red_heredoc(t_setup *setup, t_tree *tree, t_redirections *redirection);


// >>>>>>>>>>>>>>>>>>> heredoc >>>>>>>>>>>>>>>>>>>>>>
int		is_heredoc(t_tree *tree);
void	heredoc_process(t_setup *setup, t_tree *tree);
char	*get_file_name(t_setup *setup);
int		refresh_fds(t_setup *setup, char *file_name);
// int		should_expand(t_token *token);
int		should_expand(t_setup *setup);
void	expand_heredoc_input(t_setup *setup, char *input);
void	cleanup_heredoc(t_setup *setup);
void	heredoc_counter(t_setup *setup, t_tree *tree);
void	do_eof_heredoc(t_setup *setup);
void	get_delimiter(t_setup *setup, t_redirections *red);
void	maximum_heredoc_msg();


// >>>>>>>>>>>>>>>>>>>>>>> signals >>>>>>>>>>>>>>>>>>
int		*exit_status();
void	setup_signals();
void	main_sigint(int sig);
void	heredoc_sigint(int sig);
void	do_eof(t_setup *setup);
void	execute_sigint(int sig);
void	sigint_exit_status(t_setup *setup);
void	signal_status(t_setup *setup, int status);
t_setup	**get_setup_ref(void);
void	set_setup(t_setup *ptr);
t_setup	*get_setup(void);

# endif