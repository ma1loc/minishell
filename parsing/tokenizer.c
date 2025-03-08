#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_token *add_token( t_token **head, char *value, t_token_type type) // function creat new token and add it to the linked list
{
  t_token *new_token;
  t_token *current;

  new_token = malloc(sizeof(t_token));
  if(!new_token)
    return(NULL);

  new_token->value = strdup(value);  // copy the value
  new_token->type = type;
  new_token->next = NULL;

  if(*head == NULL)      // if list empty make this token the first in the list
  {
   *head = new_token;
   return(new_token);
  }

  current = *head;
  while(current->next != NULL)
  {
    current = current->next;
  }
  current->next = new_token;
  return(new_token);
}

t_token *tokenize(char *input)  // func to tokenize input string
{
  t_token *tokens;
  char buff[1024]; // buuffer to collect the characters
  int i;
  int j;

  tokens = NULL;
  i = 0;
  j = 0;
  while(input[i] != '\0')
  {
    if(input[i] == ' ')
    {
      if(j > 0)  // if buffer has word save it
      {
        buff[j] = '\0';
        add_token(&tokens, buff, TOKEN_WORD);
        j = 0;
      }
    }
    else if(input[i] == '|')
    {
      if(j > 0)
      {
        buff[j] = '\0';
        add_token(&tokens, buff, TOKEN_WORD);
        j = 0;
      }
      buff[0] = '|';
      buff[1] = '\0';
      add_token(&tokens, buff, TOKEN_PIPE);
    }
    else if(input[i] == '>' && input[i + 1] == '>')
    {
      if(j > 0)
      {
        buff[j] = '\0';
        add_token(&tokens, buff, TOKEN_APPEND);
      }
      buff[0] = '>';
      buff[1] = '>';
      buff[2] = '\0';
      add_token(&tokens, buff, TOKEN_APPEND);
      i++;
    }
    else if(input[i] == '<' && input[i + 1] == '<')
    {
      if(j > 0)
      {
        buff[j] = '\0';
        add_token(&tokens, buff, TOKEN_HERDOC);
      }
      buff[0] = '<';
      buff[1] = '<';
      buff[2] = '\0';
      add_token(&tokens, buff, TOKEN_HERDOC);
      i++;
    }
    else if(input[i] == '<')
    {
      if(j > 0)
      {
        buff[j] = '\0';
        add_token(&tokens, buff, TOKEN_RED_IN);
        j = 0;
      }
      buff[0] = '<';
      buff[1] = '\0';
      add_token(&tokens, buff, TOKEN_RED_IN);
    }
    else if(input[i] == '>')
    {
      if(j > 0)
      {
        buff[j] = '\0';
        add_token(&tokens, buff, TOKEN_RED_OUT);
        j = 0;
      }
      buff[0] = '>';
      buff[1] = '\0';
      add_token(&tokens, buff, TOKEN_RED_OUT);
    }
    else
      buff[j++] = input[i];  // if normal character add them to the buffer
    i++;
  }
  if( j > 0)
  {
    buff[j] = '\0';
    add_token(&tokens, buff, TOKEN_WORD);
  }
  return (tokens);
}

void print_tokens( t_token *tokens) // print tokens
{
  while(tokens != NULL)
  {
    printf("token => [%s], type => [%d]\n ", tokens->value, tokens->type);
    tokens = tokens->next;
  }
}


// void free_tokens(t_token *tokens)
// {
//   t_token *current;
//   t_token *next;

//   current = tokens;
//   while(current)
//   {
//     next = current->next;
//     free(current->value);  // free string
//     free(current);         // free token struct
//     current = next;
//   }
// }

// int main()
// {
//   char *input = "ls -l | cat > out.txt";
//   t_token *tokens = tokenize(input);
//   print_tokens(tokens);
//   free_tokens(tokens);
// }


// t_command *find_pipe_node(t_command *commands) //  check pipe node
// {
//     t_command *current = commands;
//     while (current)
//     {
//         if (current->type == TOKEN_PIPE)
//             return current; // Return the pipe node
//         current = current->next;
//     }
//     return NULL; // No pipe found
// }

// char *quotes_getter(char *str)
// {"ls |cat"

// }
// Token get_token(char *str ,char **s1)
// {
//   if(*s1 = strnstr(str , ">", 1))
//     return (REDIRECTION);
//   else
//     return ()

// }


// int main()
// {
//     char *input = "echo";

//     // Tokenize the input
//     t_token *tokens = tokenize(input);

//     // Print the tokens
//     printf("Tokens:\n");
//     print_tokens(tokens);
//     // free_tokens(tokens);

//     // Parse the tokens
//     t_command *commands = pars_tokens(tokens);
//     t_command *pipe_node = find_pipe_node(commands);

//     // Print the parsed commands
//     printf("\nParsed Commands:\n");
//     print_commands(commands);
//     //

//     if (pipe_node)
//     printf("Found a pipe node in the command list!\n");
//     else
//     printf("No pipe node found in the command list.\n");


//     return 0;
// }

