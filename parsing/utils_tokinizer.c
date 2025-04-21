#include "tokenizer.h"
#include "../srcs/mini_shell.h"

void process_spaces(t_tokinizer_state *state, t_token **tokens)
{
  t_quotes_info info;

  if(state->j > 0)
  {
    state->buff[state->j] = '\0';
    info = strip_quotes(state->buff);
    if(info.stripped_text != NULL)
    {
      add_token(tokens, info.stripped_text, TOKEN_WORD, info.quotes_type);
      free(info.stripped_text);
    }
    state->j = 0;
  }
  state->i++;
}

void process_special_tokens(char *input, t_tokinizer_state *state, t_token **tokens)
{
  t_quotes_info info;

  if(state->j > 0)
  {
    state->buff[state->j] = '\0';  //save any buffered word first
    info = strip_quotes(state->buff);
    if(info.stripped_text != NULL)
    {
      add_token(tokens, info.stripped_text, TOKEN_WORD, info.quotes_type);
      free(info.stripped_text);
    }
    state->j = 0;
  }
  process_operators(input, state, tokens);

}

void process_remainder_text(t_tokinizer_state *state, t_token **tokens)
{
  t_quotes_info info;

  if(state->j > 0)
  {
    state->buff[state->j] = '\0';
    info = strip_quotes(state->buff);
    if(info.stripped_text != NULL)
    {
      add_token(tokens, info.stripped_text, TOKEN_WORD, info.quotes_type);
      free(info.stripped_text);
    }
    state->j = 0;
  }
}

void process_dollar(char *input, t_tokinizer_state *state, t_token **tokens)
{

  t_quotes_info info;
  t_token *new_token;
  int is_space;

  is_space = -1;
      // Check for $" pattern (special case for $"string")
      if (input[state->i + 1] == '"')
      {
          // int quote_start = state->i + 1;  // Position of the opening quote
          int content_start = state->i + 2;  // Position after the opening quote
          int content_end = content_start;

          // Find the closing quote
          while (input[content_end] && input[content_end] != '"')
              content_end++;

          if (input[content_end] == '"') {
              // We found a closing quote - extract just the content
              int content_length = content_end - content_start;
              char *content = malloc(content_length + 1);
              if (content) {
                  strncpy(content, input + content_start, content_length);
                  content[content_length] = '\0';

                  // Add the content as a token (without $ and quotes)
                  new_token = add_token(tokens, content, TOKEN_WORD, 0);
                  new_token->is_space = (input[content_end + 1] == ' ' || input[content_end + 1] == '\t') ? 1 : -1;
                  free(content);
                  // Skip past this entire construct
                  state->i = content_end + 1;
                  return;
              }
          }
      }
  state->buff[state->j++] = input[state->i++];
  if (input[state->i] == '?') // expand exit stat ($?)
    state->buff[state->j++] = input[state->i++];
  while (input[state->i] != '\0' && (isalnum(input[state->i]) || input[state->i] == '_'))
  {
      state->buff[state->j++] = input[state->i++];
  }
  if(input[state->i] == ' ' || input[state->i] == '\t')
    is_space = 1;
  state->buff[state->j] = '\0';  //save any buffered word first
  info = strip_quotes(state->buff);
  if(info.stripped_text != NULL)
  {
    new_token = add_token(tokens, info.stripped_text, TOKEN_WORD, info.quotes_type);
    new_token->is_space = is_space;
    free(info.stripped_text);
  }
  state->j = 0;
}

void process_quotes(char *input, t_tokinizer_state *state, t_setup *setup, t_token **tokens)
{
    (void)setup;
    char quote_char;
    t_quotes_info info;
    t_token *new_token;
    int is_space;

    is_space = -1;
    quote_char = input[state->i];
    state->buff[state->j++] = input[state->i++]; // add opening quote
    while(input[state->i] != '\0' && input[state->i] != quote_char) // copy everything inside quotes
    {
      state->buff[state->j++] = input[state->i++];
    }
    state->buff[state->j++] = input[state->i++]; // Add closing quote
    if (input[state->i] == ' ')
      is_space = 1;
    state->buff[state->j] = '\0';  //save any buffered word first
    info = strip_quotes(state->buff);
    if(info.stripped_text != NULL)
    {
      new_token = add_token(tokens, info.stripped_text, TOKEN_WORD, info.quotes_type);
      new_token->is_space = is_space;
      free(info.stripped_text);
    }
    state->j = 0;
}


