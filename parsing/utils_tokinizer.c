#include "tokenizer.h"
#include "../srcs/mini_shell.h"

void process_spaces(char *input, t_tokinizer_state *state, t_token **tokens)
{
  char *stripped;

  if(state->j > 0)
  {
    state->buff[state->j] = '\0';
    stripped = strip_quotes(state->buff);
    if(stripped != NULL)
    {
      add_token(tokens, stripped, TOKEN_WORD);
      free(stripped);
    }
    state->j = 0;   // in_word = 0;
  }
  state->i++;
}
void process_operators(char *input, t_tokinizer_state *state, t_token **tokens)
{
  if(input[state->i] == '|')
  {
    add_token(tokens, "|", TOKEN_PIPE);
    state->i++;
  }
  else if(input[state->i] == '>' && input[state->i + 1] == '>')
  {
    add_token(tokens, ">>", TOKEN_APPEND);
    state->i += 2;
  }
  else if(input[state->i] == '<' && input[state->i + 1] == '<')
  {
    add_token(tokens, "<<", TOKEN_HERDOC);
    state->i += 2;
  }
  else if(input[state->i] == '>')
  {
    add_token(tokens, ">", TOKEN_RED_OUT);
    state->i++;
  }
  else if(input[state->i] == '<')
  {
    add_token(tokens, "<", TOKEN_RED_IN);
    state->i++;
  }
}

void process_special_tokens(char *input, t_tokinizer_state *state, t_token **tokens)
{
  char *stripped;

  if(state->j > 0)
  {
    state->buff[state->j] = '\0';  //save any buffered word first
    stripped = strip_quotes(state->buff);
    if(stripped != NULL)
    {
      add_token(tokens, stripped, TOKEN_WORD);
      free(stripped);
    }
    state->j = 0;
  }
  process_operators(input, state, tokens);

}

void process_remainder_text(char *input, t_tokinizer_state *state, t_token **tokens)
{
  char *stripped;

  if(state->j > 0)
  {
    state->buff[state->j] = '\0';
    stripped = strip_quotes(state->buff);
    if(stripped != NULL)
    {
      add_token(tokens, stripped, TOKEN_WORD);
      free(stripped);
    }
    state->j = 0;   // in_word = 0;
  }
}


void process_quotes(char *input, t_tokinizer_state *state)
{
  {
    char quote_char;

    quote_char = input[state->i];
    state->buff[state->j++] = input[state->i++]; // Add opening quote

    // Copy everything inside quotes
    while(input[state->i] != '\0' && input[state->i] != quote_char)
    {
      state->buff[state->j++] = input[state->i++];
    }

    if(input[state->i] == '\0')
    {
      printf("syntax error\n");
      return ;
    }

    state->buff[state->j++] = input[state->i++]; // Add closing quote
  }
}

void process_normal_word(char *input, t_tokinizer_state *state)
{
  state->buff[state->j++] = input[state->i++];
}

