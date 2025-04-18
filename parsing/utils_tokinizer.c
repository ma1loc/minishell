#include "tokenizer.h"
#include "../srcs/mini_shell.h"


// void	ft_putstr_fd(char *s, int fd)   //////// remove it
// {
// 	size_t	i;

// 	if (fd < 0 || !s)
// 		return ;
// 	i = 0;
// 	while (s[i])
// 	{
// 		write(fd, &s[i], 1);
// 		i++;
// 	}

// 	// >>> put here the exit status to exit the program.
// }
// void    ft_exit(t_setup *setup, int exit_stat)  //////// remove it
// {
//     if (setup)
//     {
//         if (exit_stat == EXIT_SUCCESS)             // >>> exit 0
//         setup->exit_stat = EXIT_SUCCESS;
//         else if (exit_stat == EXIT_FAILURE)           // >>> exit 1
//             setup->exit_stat = EXIT_FAILURE;
//         else if (exit_stat == SYNTAX_ERROR)   // >>> exit 2
//             setup->exit_stat = SYNTAX_ERROR;
//         else if (exit_stat == CMD_NOT_FOUND)  // >>> exit 127
//             setup->exit_stat = CMD_NOT_FOUND;
//         else if (exit_stat == CMD_NOT_EXEC)   // >>> exit 126
//             setup->exit_stat = CMD_NOT_EXEC;
//     }
// }
// void    ft_perror(t_setup *setup, char *msg, int exit_stat) //////// remove it
// {
//     // >>> garbage collector have to create and call here <<<
//     if (msg)
//         ft_putstr_fd(msg, STDERR_FILENO);
//     else
//         perror("");
//     ft_exit(setup, exit_stat);
// }

////////////////////////////////////////////////////////////////////// 
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
void process_operators(char *input, t_tokinizer_state *state, t_token **tokens)
{
  t_quotes_info info;

  if(input[state->i] == '|')
  {
    add_token(tokens, "|", TOKEN_PIPE, info.quotes_type);
    state->i++;
  }
  else if(input[state->i] == '>' && input[state->i + 1] == '>')
  {
    add_token(tokens, ">>", TOKEN_APPEND, info.quotes_type);
    state->i += 2;
  }
  else if(input[state->i] == '<' && input[state->i + 1] == '<')
  {
    add_token(tokens, "<<", TOKEN_HERDOC, info.quotes_type);
    state->i += 2;
  }
  else if(input[state->i] == '<' && input[state->i + 1] == '>')
  {
    add_token(tokens, "<>", TOKEN_RED_INOUT, info.quotes_type);
    state->i += 2;
  }
  else if(input[state->i] == '>')
  {
    add_token(tokens, ">", TOKEN_RED_OUT, info.quotes_type);
    state->i++;
  }
  else if(input[state->i] == '<')
  {
    add_token(tokens, "<", TOKEN_RED_IN, info.quotes_type);
    state->i++;
  }
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

// void process_dollar_in_quotes(char *input, t_tokinizer_state *state, t_token **tokens)
// {

//   t_quotes_info info;
//   t_token *new_token;
//   int is_space = -1;
//   char quote_char;
  
//   state->buff[state->j++] = input[state->i++];
//   if (input[state->i] == '?') // expand exit stat ($?)
//     state->buff[state->j++] = input[state->i++];
//   while (input[state->i] != '\0' && (isalnum(input[state->i]) || input[state->i] == '_'))
//   {
//       state->buff[state->j++] = input[state->i++];  
//   }
//   while(input[state->i] == ' ' || input[state->i] == '\t')
//   {
//     state->buff[state->j++] = input[state->i++];
//     is_space = 1;
//   }
//   if(input[state->i] == '\'' && (input[state->i + 1] == '$' || !isalnum(input[state->i])))
//   {
//     quote_char = input[state->i];
//     state->buff[state->j++] = input[state->i++];
//     while (input[state->i] != '\0' && input[state->i] != '"')
//     {
//       state->buff[state->j++] = input[state->i++];  
//     }
//     if(input[state->i] == quote_char)
//       state->buff[state->j++] = input[state->i++];
//   }
//   if(input[state->i] == '"')
//     state->buff[state->j++] = input[state->i++];
//   state->buff[state->j] = '\0';  //save any buffered word first
//   info = strip_quotes(state->buff);
//   if(info.stripped_text != NULL)
//   {
//     new_token = add_token(tokens, info.stripped_text, TOKEN_WORD, info.quotes_type);
//     new_token->is_space = is_space;
//     free(info.stripped_text);
//   }
//   state->j = 0;
// }
void process_dollar(char *input, t_tokinizer_state *state, t_token **tokens)
{

  t_quotes_info info;
  t_token *new_token;
  int is_space = -1;
  
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
    int is_space = -1;
    // if(state->j > 0)
    // {
    // state->buff[state->j] = '\0';
    // info = strip_quotes(state->buff);
    // // printf("-->%s\n", info.stripped_text);
    // if(info.stripped_text != NULL)
    // {
    //   add_token(tokens, info.stripped_text, TOKEN_WORD, info.quotes_type);
    //   free(info.stripped_text);
    // }
    // state->j = 0;
    // }
    quote_char = input[state->i];
    state->buff[state->j++] = input[state->i++]; // add opening quote
    // copy everything inside quotes
    while(input[state->i] != '\0' && input[state->i] != quote_char)
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

void process_normal_word(char *input, t_tokinizer_state *state)
{
  state->buff[state->j++] = input[state->i++];
}

