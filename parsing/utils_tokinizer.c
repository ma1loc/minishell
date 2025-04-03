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
void process_spaces(t_tokinizer_state *state, t_token **tokens, t_setup *setup)
{
  char *stripped;

  if(state->j > 0)
  {
    state->buff[state->j] = '\0';
    stripped = strip_quotes(state->buff, setup);
    if(stripped != NULL)
    {
      add_token(tokens, stripped, TOKEN_WORD);
      free(stripped);
    }
    state->j = 0;
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
  else if(input[state->i] == '<' && input[state->i + 1] == '>')
  {
    add_token(tokens, "<>", TOKEN_RED_INOUT);
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

void process_special_tokens(char *input, t_tokinizer_state *state, t_token **tokens, t_setup *setup)
{
  char *stripped;

  if(state->j > 0)
  {
    state->buff[state->j] = '\0';  //save any buffered word first
    stripped = strip_quotes(state->buff, setup);
    if(stripped != NULL)
    {
      add_token(tokens, stripped, TOKEN_WORD);
      free(stripped);
    }
    state->j = 0;
  }
  process_operators(input, state, tokens);

}

void process_remainder_text(t_tokinizer_state *state, t_token **tokens, t_setup *setup)
{
  char *stripped;

  if(state->j > 0)
  {
    state->buff[state->j] = '\0';
    stripped = strip_quotes(state->buff, setup);
    if(stripped != NULL)
    {
      add_token(tokens, stripped, TOKEN_WORD);
      free(stripped);
    }
    state->j = 0;   // in_word = 0;
  }
}


void process_quotes(char *input, t_tokinizer_state *state, t_setup *setup)
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
      // printf("syntax error\n");
      ft_perror(setup, "syntax error near unexpected token\n", SYNTAX_ERROR);
      return ;
    }

    state->buff[state->j++] = input[state->i++]; // Add closing quote
  }
}

void process_normal_word(char *input, t_tokinizer_state *state)
{
  state->buff[state->j++] = input[state->i++];
}

