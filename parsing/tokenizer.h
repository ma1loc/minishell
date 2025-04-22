#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// #include "../srcs/mini_shell.h"

typedef struct s_setup t_setup;
typedef struct s_env t_env;

typedef enum e_token_type
{
  TOKEN_WORD = 0,
  TOKEN_PIPE,
  TOKEN_RED_IN,
  TOKEN_RED_OUT,
  TOKEN_APPEND,
  TOKEN_HERDOC,
  TOKEN_RED_INOUT,
} t_token_type;

typedef struct s_process_data
{
	char	*str;
	char	*result;
	int		i;
	int		j;
}	t_process_data;

typedef struct s_content_info
{
	char	*input;
	char	*content;
	int		start;
	int		length;
	int		end;
}	t_content_info;

typedef struct s_expand_data {
  int var_index;
  int buff_index;
  char var_name[256];
  char buff[1024];
  char *ptr;
  char *env_value;
} t_expand_data;

typedef struct s_quotes_info
{
  char *stripped_text;
  int quotes_type;
} t_quotes_info;

typedef struct s_tokinizer_state // struct for state of the token to use i and j and buff
{
  int i;
  int j;
  char buff[1024];

} t_tokinizer_state;

typedef struct s_token  // struct for tokenize input
{
  char *value; // text of the token
  t_token_type type;  // token type
  struct s_token *next;
  t_quotes_info *quotes_info;
  int is_space;
  int is_split;
} t_token;

typedef struct s_insert_info
{
    t_token **head;
    char *value;
    int token_type;
    int quotes_type;
} t_insert_info;

typedef struct s_args_list // struct for linked list for args
{
  char *value;
  t_token_type type;
  struct s_args_list *next;
} t_args_list;

typedef struct s_redirections  // struct for linked list for redit
{
  char *file_name;
  t_token_type type;
  struct s_redirections *next;
} t_redirections;

typedef struct s_command // struct for linked list of cmds
{
  char *name;    // main commande (like "ls")
  char **args;   // list args for the commande
  t_redirections *redirections;  // list or redir
  t_token_type type;         // token type
  struct s_command *next;
} t_command;

typedef struct s_commmande_state // struct for state of cmd to use cuurent and new
{
  t_command *current_cmd;
  t_command *new_cmd;
  t_setup *setup; //////
  int args_count;
} t_commande_state;

typedef struct s_tree   // struct for the tree
{
  char *name;
  char **args;
  t_command *cmd;
  t_token_type type;  // node command or pipe
  t_redirections *redirections;
  struct s_tree *left; // left command
  struct s_tree *right; // right command
} t_tree;


t_token *tokenize(t_setup *setup);
t_command *pars_tokens(t_setup *setup);
t_tree *build_tree_commande(t_command *commandes);
t_args_list *add_args_to_list(t_args_list **list_head, t_token *token);
int count_args_list(t_args_list *args);
void fill_array(t_args_list *args_list, t_command *commads);
void free_list_args(t_args_list *list_args);
t_redirections *new_redirection(char *file_name, t_token_type type);
void add_redirection_to_list( t_command *cmd, char *file_name, t_token_type type);
void free_redirections(t_redirections *redir);
void process_spaces(t_tokinizer_state *state, t_token **tokens);
void process_special_tokens(char *input, t_tokinizer_state *state, t_token **tokens);
void process_operators(char *input, t_tokinizer_state *state, t_token **tokens);
void process_quotes(char *input, t_tokinizer_state *state, t_token **tokens);
void process_normal_word(char *input, t_tokinizer_state *state);
void process_remainder_text(t_tokinizer_state *state, t_token **tokens);
void creat_node_next_commande(t_commande_state *state);
void creat_node_pipe_commande(t_commande_state *state);
t_command *creat_new_node_command(t_command *commandes);
void process_token_type_pipe(t_commande_state *state, t_args_list **list_args);
t_token *process_token_type_redir(t_commande_state *state, t_token *current);
void process_args_last_cmd(t_commande_state *state, t_args_list *list_args);
void expand_env_vars(t_token *tokens, t_setup *setup);
char *get_env_value(char *name, t_setup *setup);
char *expand_env_in_string(char *str, t_setup *setup);
void process_dollar(char *input, t_tokinizer_state *state, t_token **tokens);
t_token *add_token( t_token **head, char *value, t_token_type type, int quotes_type);
t_quotes_info strip_quotes(char *str);
void    ft_perror(t_setup *setup, char *msg, int exit_stat);  /// remove it later
char	*ft_itoa_(int n);
void	remove_token(t_token **head, t_token *current);
int check_space(char *str);
bool check_current_type(enum e_token_type type);
t_token *insert_new_token(t_insert_info info, t_token *last_inserted);
int extract_word(char *input, int i, char *buff);
t_token *process_word(t_insert_info info, char *buff, t_token *last_inserted);
int skip_whitespace(char *input, int i);
t_token *process_split_token(char *input, t_token **head, t_token *last_inserted, int quotes_type);
int get_quotes_type(t_token *token);
t_token *set_last_inserted(t_token *prev);
t_token *handle_split_token(t_token *current, t_token *prev, t_token **head);
void handel_is_split(t_token *tokens, t_token **head);
t_quotes_info	strip_quotes(char *str);
void	process_quote_char(t_process_data *data, t_quotes_info *info);
int check_syntax(char *input, int len, int *i);
void check_unclosed_quotes(t_setup *setup, int *i, int *in_quotes, char *quotes_char);
int handle_syntax_error(t_setup *setup, int in_quotes);
int check_original_cases(char *input, int len, int *i);
int check_quotes_syntax(t_setup *setup);
int check_redirections(char *input, int len, int *i);
int check_pipes(char *input, int len, int *i);
void	process_token(t_commande_state *state, t_token *current, t_args_list **list_args);
int	join_tokens(t_token **current, t_token *head);
void	set_command_name(t_commande_state *state, t_token *current, int *found_cmd_name);
void	creat_node_pipe_commande(t_commande_state *state);
void	creat_node_next_commande(t_commande_state *state);
t_command	*creat_new_node_command(t_command *commandes);
char	*ft_strjoin_(char *s1, char *s2);
char *skip_spaces_while_expand(t_token *token,char *str);
void copy_env_value_if_valid(t_expand_data *data, t_token *token);
int expand_exit_status(t_expand_data *data, t_setup *setup);
char *extract_var_name(t_expand_data *data);
int handle_dollar_expansion(t_expand_data *data, t_setup *setup);
void handle_double_operator(char *input, t_tokinizer_state *state, t_token **tokens, t_quotes_info info);
void handle_single_operator(char *input, t_tokinizer_state *state, t_token **tokens, t_quotes_info info);
int is_single_quote(char *value);
void process_args(t_args_list *current, t_command *cmd, int *i);
int	skip_whitespace(char *input, int i);
int	handle_dollar_dquotes(char *input, t_tokinizer_state *state, t_quotes_info info, t_token **tokens);
int	handle_dollar_squotes(char *input, t_tokinizer_state *state, t_quotes_info info, t_token **tokens);
int process_token_content(t_content_info *c_info, t_token **tokens, t_quotes_info info,t_tokinizer_state *state);
int handle_dollar_quotes(char *input, t_tokinizer_state *state, t_token **tokens, t_quotes_info *info);



#endif