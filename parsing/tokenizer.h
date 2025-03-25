#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdbool.h>
// #include "../srcs/mini_shell.h"

typedef struct s_setup t_setup;

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

} t_token;

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

// t_token *tokenize(char *input);
t_token *tokenize(char *input, t_setup *setup);
t_command *pars_tokens(t_token *tokens);
void print_tokens(t_token *tokens);  // remov later
void print_commands(t_command *cmd);  // remove later
void free_tokens(t_token *tokens);    // use it if needed
//
t_tree *build_tree_commande(t_command *commandes);
t_command *find_pipe_node(t_command *commands);   // remove later
t_args_list *add_args_to_list(t_args_list **list_head, t_token *token);
int count_args_list(t_args_list *args);
void fill_array(t_args_list *args_list, t_command *commads);
void free_list_args(t_args_list *list_args);
void print_tree(t_tree *root, int level); // remove later
/////////////////////////////////
t_redirections *new_redirection(char *file_name, t_token_type type);
void add_redirection_to_list( t_command *cmd, char *file_name, t_token_type type);
void free_redirections(t_redirections *redir);

//////////////////////
void process_spaces(t_tokinizer_state *state, t_token **tokens);
void process_special_tokens(char *input, t_tokinizer_state *state, t_token **tokens);
void process_operators(char *input, t_tokinizer_state *state, t_token **tokens);
void process_quotes(char *input, t_tokinizer_state *state);
// void process_quotes(char *input, t_tokinizer_state *state, t_setup *setup);

void process_normal_word(char *input, t_tokinizer_state *state);
void process_remainder_text(t_tokinizer_state *state, t_token **tokens);
///////////////////////
void process_token(t_commande_state *state, t_token *current, t_args_list **list_args);
void creat_node_next_commande(t_commande_state *state);
void creat_node_pipe_commande(t_commande_state *state);
t_command *creat_new_node_command(t_command *commandes);
// void process_token_type_word(t_commande_state *state, t_token *current, t_args_list **list_args);
void process_token_type_pipe(t_commande_state *state, t_args_list **list_args);
t_token *process_token_type_redir_in_her(t_commande_state *state, t_token *current);
// void process_token_type_redir_out_app(t_commande_state *state, t_token *current);
void process_args_last_cmd(t_commande_state *state, t_args_list *list_args);





t_token *add_token( t_token **head, char *value, t_token_type type);
char *strip_quotes(char *str);

#endif