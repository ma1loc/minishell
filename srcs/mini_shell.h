/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:06:23 by yanflous          #+#    #+#             */
/*   Updated: 2025/04/23 13:06:25 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define PATH_MAX 4096
# define HERE_DOC_MAX 16
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define SYNTAX_ERROR 2
# define CMD_NOT_FOUND 127
# define CMD_NOT_EXEC 126
# define EXIT_SEGINT 130
# define EXIT_QUIT 131
# define EQUAL 1
# define APPEND 2

typedef enum e_token_type
{
	TOKEN_WORD = 0,
	TOKEN_PIPE,
	TOKEN_RED_IN,
	TOKEN_RED_OUT,
	TOKEN_APPEND,
	TOKEN_HERDOC,
}					t_token_type;

typedef struct s_process_data
{
	char			*str;
	char			*result;
	int				i;
	int				j;
}					t_process_data;

typedef struct s_content_info
{
	char			*input;
	char			*content;
	int				start;
	int				length;
	int				end;
}					t_content_info;

typedef struct s_expand_data
{
	int				var_index;
	int				buff_index;
	char			var_name[256];
	char			buff[1024];
	char			*ptr;
	char			*env_value;
}					t_expand_data;

typedef struct s_quotes_info
{
	char			*stripped_text;
	int				quotes_type;
}					t_quotes_info;

typedef struct s_tokinizer_state
{
	int				i;
	int				j;
	char			buff[1024];

}					t_tokinizer_state;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	t_quotes_info	*quotes_info;
	int				is_space;
	int				is_split;
}					t_token;

typedef struct s_insert_info
{
	t_token			**head;
	char			*value;
	int				token_type;
	int				quotes_type;
}					t_insert_info;

typedef struct s_args_list
{
	char				*value;
	t_token_type		type;
	struct s_args_list	*next;
}					t_args_list;

typedef struct s_redirections
{
	char					*file_name;
	t_token_type			type;
	struct s_redirections	*next;
}					t_redirections;

typedef struct s_command
{
	char				*name;
	char				**args;
	t_redirections		*redirections;
	t_token_type		type;
	struct s_command	*next;
}					t_command;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_heredoc
{
	char			*delimiter;
	int				fd[HERE_DOC_MAX];
	char			*file_name[HERE_DOC_MAX];
	int				qoutes_type;
	char			*delim_map[HERE_DOC_MAX];
}					t_heredoc;

typedef struct s_tree
{
	char			*name;
	char			**args;
	t_command		*cmd;
	t_token_type	type;
	t_redirections	*redirections;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

typedef struct s_setup
{
	int				i;
	char			*input;
	t_env			*env;
	t_token			*token;
	t_command		*cmd;
	t_tree			*tree;
	char			*pwd;
	char			*oldpwd;
	char			*cmd_path;
	char			**envp;
	char			**exec_env;
	int				exit_stat;
	t_heredoc		*heredoc;
	int				heredoc_flag;
	int				fork_flag;
	int				heredoc_counter;
}					t_setup;

typedef struct s_commmande_state
{
	t_command		*current_cmd;
	t_command		*new_cmd;
	t_setup			*setup;
	int				args_count;
}					t_commande_state;

typedef struct s_mem
{
	void			*ptr;
	struct s_mem	*next;
}					t_mem;

typedef struct s_gc
{
	t_mem			*mem_list;
	int				total_allocs;
	size_t			total_bytes;
}					t_gc;

extern t_gc			*g_gc;

typedef enum e_export_type
{
	KEY_ONLY,
	ASSIGN_VALUE,
	APPEND_VALUE
}					t_export_type;

size_t				ft_strlen(char *str);
char				**ft_split(char *str, char separator);
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(char *s1, char *s2, size_t n);
char				*ft_strdup(char *s1);
char				*ft_strjoin(char *s1, char *s2);
void				ft_putstr_fd(char *s, int fd);
int					ft_strcmp(char *s1, char *s2);
void				*ft_memset(void *s, int c, size_t len);
char				*ft_substr(char *s1, size_t start, size_t len);
int					ft_isdigit(char *str);
char				*ft_strnstr(char *str, char *to_find, size_t n);
char				*ft_strchr(char *s, int c);
char				*ft_itoa(int n);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
t_env				*ft_lstlast(t_env *lst);
void				ft_lstadd_back(t_env **lst, t_env *new);
int					ft_atoi(char *str);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, unsigned int n);

t_export_type		get_export_type(char *arg);

void				cd_cmd(t_setup *setup);
void				pwd_cmd(t_setup *setup);
int					get_pwd(t_setup *setup);
void				echo_cmd(t_setup *setup);
t_env				*init_env(char **env, t_env *env_list);
void				env_cmd(t_setup *setup);
void				unset_cmd(t_setup *setup);
int					cd(t_setup *setup);
void				exit_cmd(t_setup *setup);
void				export_cmd(t_setup *setup);
void				export_display(t_setup *setup);
int					export_key_only(t_setup *setup, char *key);
void				update_env(t_setup *setup, char *key, char *value);
void				append_to_env(t_setup *setup, char *key, char *value);
t_env				*get_env_key(t_setup *setup, char *key);
void				ft_perror(t_setup *setup, char *msg, int exit_stat);
int					is_valid_identifier(char *key);
int					is_valid_number(char *str);
char				*char_to_str(char c);
void				allocation_failed_msg(void);
t_gc				*gc_init(void);
void				*gc_malloc(t_gc *gc, size_t size);
void				gc_cleanup(t_gc *gc);
void				gc_destroy(t_gc *gc);
// void	gc_print_stats(t_gc *gc); // >>> to remove later on
void				gc_free(t_gc *gc, void *ptr);
t_token				*tokenize(t_setup *setup);
t_command			*pars_tokens(t_setup *setup);
t_tree				*build_tree_commande(t_command *commandes);
t_args_list			*add_args_to_list(t_args_list **list_head, t_token *token);
int					count_args_list(t_args_list *args);
void				fill_array(t_args_list *args_list, t_command *commads);
// void free_list_args(t_args_list *list_args);
t_redirections		*new_redirection(char *file_name, t_token_type type);
void				add_redirection_to_list(t_command *cmd, char *file_name,
						t_token_type type);
// void free_redirections(t_redirections *redir);
void				process_spaces(t_tokinizer_state *state, t_token **tokens);
void				process_special_tokens(char *input,
						t_tokinizer_state *state, t_token **tokens);
void				process_operators(char *input, t_tokinizer_state *state,
						t_token **tokens);
void				process_quotes(char *input, t_tokinizer_state *state,
						t_token **tokens);
void				process_normal_word(char *input, t_tokinizer_state *state);
void				process_remainder_text(t_tokinizer_state *state,
						t_token **tokens);
void				creat_node_next_commande(t_commande_state *state);
void				creat_node_pipe_commande(t_commande_state *state);
t_command			*creat_new_node_command(t_command *commandes);
void				process_token_type_pipe(t_commande_state *state,
						t_args_list **list_args);
t_token				*process_token_type_redir(t_commande_state *state,
						t_token *current);
void				process_args_last_cmd(t_commande_state *state,
						t_args_list *list_args);
void				expand_env_vars(t_token *tokens, t_setup *setup);
char				*get_env_value(char *name, t_setup *setup);
char				*expand_env_in_string(char *str, t_setup *setup);
void				process_dollar(char *input, t_tokinizer_state *state,
						t_token **tokens);
t_token				*add_token(t_token **head, char *value, t_token_type type,
						int quotes_type);
t_quotes_info		strip_quotes(char *str);
// void    ft_perror(t_setup *setup, char *msg, int exit_stat);
/// remove it later
char				*ft_itoa_(int n);
void				remove_token(t_token **head, t_token *current);
int					check_space(char *str);
bool				check_current_type(enum e_token_type type);
t_token				*insert_new_token(t_insert_info info,
						t_token *last_inserted);
int					extract_word(char *input, int i, char *buff);
t_token				*process_word(t_insert_info info, char *buff,
						t_token *last_inserted);
int					skip_whitespace(char *input, int i);
t_token				*process_split_token(char *input, t_token **head,
						t_token *last_inserted, int quotes_type);
int					get_quotes_type(t_token *token);
t_token				*set_last_inserted(t_token *prev);
t_token				*handle_split_token(t_token *current, t_token *prev,
						t_token **head);
void				handel_is_split(t_token *tokens, t_token **head);
t_quotes_info		strip_quotes(char *str);
void				process_quote_char(t_process_data *data,
						t_quotes_info *info);
int					check_syntax(char *input, int len, int *i);
void				check_unclosed_quotes(t_setup *setup, int *i,
						int *in_quotes, char *quotes_char);
int					handle_syntax_error(t_setup *setup, int in_quotes);
int					check_original_cases(char *input, int len, int *i);
int					check_quotes_syntax(t_setup *setup);
int					check_redirections(char *input, int len, int *i);
int					check_pipes(char *input, int len, int *i);
void				process_token(t_commande_state *state, t_token *current,
						t_args_list **list_args);
int					join_tokens(t_token **current, t_token *head);
void				set_command_name(t_commande_state *state, t_token *current,
						int *found_cmd_name);
void				creat_node_pipe_commande(t_commande_state *state);
void				creat_node_next_commande(t_commande_state *state);
t_command			*creat_new_node_command(t_command *commandes);
char				*ft_strjoin_(char *s1, char *s2);
char				*skip_spaces_while_expand(t_token *token, char *str);
void				copy_env_value_if_valid(t_expand_data *data,
						t_token *token);
int					expand_exit_status(t_expand_data *data, t_setup *setup);
char				*extract_var_name(t_expand_data *data);
int					handle_dollar_expansion(t_expand_data *data,
						t_setup *setup);
void				handle_double_operator(char *input,
						t_tokinizer_state *state, t_token **tokens,
						t_quotes_info info);
void				handle_single_operator(char *input,
						t_tokinizer_state *state, t_token **tokens,
						t_quotes_info info);
int					is_single_quote(char *value);
void				process_args(t_args_list *current, t_command *cmd, int *i);
int					skip_whitespace(char *input, int i);
int					handle_dollar_dquotes(char *input, t_tokinizer_state *state,
						t_quotes_info info, t_token **tokens);
int					handle_dollar_squotes(char *input, t_tokinizer_state *state,
						t_quotes_info info, t_token **tokens);
int					process_token_content(t_content_info *c_info,
						t_token **tokens, t_quotes_info info,
						t_tokinizer_state *state);
int					handle_dollar_quotes(char *input, t_tokinizer_state *state,
						t_token **tokens, t_quotes_info *info);
void				handle_question_mark(char *input, t_tokinizer_state *state);
t_setup				*start_setup(int argc, char **argv, char **env);
int					is_built_in(char *name);
t_setup				*shell_env_setup(char **env);
char				*path_resolver(t_setup *setup);
char				**update_exec_envp(t_setup *setup, t_env *cur_env);
void				execution(t_tree *tree, t_setup *setup);
void				execute_internals(t_command *cmd, t_setup *setup);
void				execute_commands(t_tree *tree, t_setup *setup);
void				execute_pipes(t_tree *tree, t_setup *setup);
void				set_pipe(t_setup *setup, int *fd);
pid_t				set_first_fork(t_setup *setup, int *fd);
pid_t				set_second_fork(t_setup *setup, pid_t pid_1, int *fd);
pid_t				set_fork(t_setup *setup);
void				command_not_found(t_setup *setup);
void				execute_redirections(t_tree *tree, t_setup *setup);
int					red_input(t_setup *setup, t_tree *tree,
						t_redirections *redirection);
int					red_append(t_setup *setup, t_tree *tree,
						t_redirections *redirection);
int					red_output(t_setup *setup, t_tree *tree,
						t_redirections *redirection);
int					red_heredoc(t_setup *setup, t_redirections *redirection);
int					is_heredoc(t_tree *tree);
void				heredoc_process(t_setup *setup, t_tree *tree);
char				*get_file_name(t_setup *setup);
int					refresh_fds(t_setup *setup, char *file_name);
void				expand_heredoc_input(t_setup *setup, char *input);
void				cleanup_heredoc(t_setup *setup);
void				heredoc_counter(t_setup *setup, t_tree *tree);
void				do_eof_heredoc(t_setup *setup);
void				get_delimiter(t_setup *setup, t_redirections *red);
void				maximum_heredoc_msg(void);
int					*exit_status(void);
void				setup_signals(void);
void				main_sigint(int sig);
void				heredoc_sigint(int sig);
void				do_eof(t_setup *setup);
void				execute_sigint(int sig);
void				sigint_exit_status(t_setup *setup);
void				signal_status(t_setup *setup, int status);
t_setup				**get_setup(void);
void				close_fds(t_setup *setup);
char				*readline_free(char *input);

#endif
