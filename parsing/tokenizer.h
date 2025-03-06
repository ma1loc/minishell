#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef enum e_token_type
{
  TOKEN_WORD = 1,
  TOKEN_PIPE,
  TOKEN_RED_IN,
  TOKEN_RED_OUT,
  TOKEN_APPEND,
  TOKEN_HERDOC
} t_token_type;

typedef struct s_token  // struct for tokenize input
{
  char *value; // text of the token
  t_token_type type;  // token type
  struct s_token *next;

} t_token;

typedef struct s_command // struct for parse tokens
{
  char *name;    // main commande (like "ls")
  char **args;   // list args for the commande
  char *input_file; // file to red input <
  char *output_file; // file to red output
  // int piped;   // commande part of pipe
  t_token_type type;
  struct s_command *next;
} t_command;

typedef struct s_tree
{
  t_token_type type;  // node command or pipe
  char *value; // command name
  char **args;
  char *input_file;   // if <
  char *out_putfile;  // if >
  struct s_tree *left; // left command
  struct s_tree *right; // right command
} t_tree;

t_token *tokenize(char *input);
t_command *pars_tokens(t_token *tokens);
void print_tokens(t_token *tokens);
void print_commands(t_command *cmd);
void free_tokens(t_token *tokens);
//
t_command *find_pipe_node(t_command *commands);
#endif