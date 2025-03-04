#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef enum e_token_type
{
  TOKEN_WORD = 1,
  TOKEN_PIPE,
  TOKEN_RED_IN,
  TOKEN_RED_OUT
} t_token_type;

typedef struct s_token
{
  char *value; // text of the token
  t_token_type type;  // token type  // ls -la | grep "tete" 
  struct s_token *next;

} t_token;


#endif