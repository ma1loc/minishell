#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strip_quotes(char *str) // func remove quotes for str
{
  char *rslt;
  int len;
  int i;
  int j;

  if(!str)
    return (NULL);
  len = strlen(str);
  rslt = malloc(len + 1);
  if(!rslt)
    return (NULL);
  i = 0;
  j = 0;
  while(i < len)
  {
    if(str[i] != '"' && str[i] != '\'')
    {
      rslt[j] = str[i];
      j++;
    }
    i++;
  }
  rslt[j] = '\0';
  if(j == 0)  // ensure that not return empy string
  {
    // printf("strip_quotes: empty string detected\n");  // debugging msg
    free(rslt);
    return(NULL);
  }
  return(rslt);
}

int check_quotes_syntax(char *input) // fuc to check if quoest match inclosed or no
{
  int i;
  int in_quoets;
  char quoest_char;

  i = 0;
  in_quoets = 0;
  quoest_char = 0;

  while(input[i] != '\0')
  {
    if(input[i] == '"' || input[i] == '\'' && quoest_char == input[i] || in_quoets == 0)
    {
      if(!in_quoets)
      {
        in_quoets = 1;
        quoest_char = input[i];
      }
      else
      {
        in_quoets = 0;
        quoest_char = 0;
      }
    }
    i++;
  }
  if(in_quoets)
  {
    printf("syntax error\n");
    return(1);
  }
  return(0);
}


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
  char quout_char;
  char *stripped;

  tokens = NULL;
  i = 0;
  j = 0;
  quout_char = 0;
  if(!input)
    return NULL;
  if(check_quotes_syntax(input) != 0)
    return (NULL);
  while(input[i] != '\0')
  {
    if ((input[i] == '"' || input[i] == '\'') && quout_char == 0)  // this insure that if "ls -la" become single commande name
    {
      quout_char = input[i];
      if(j > 0)
      {
        buff[j] = '\0';
        add_token(&tokens, buff, TOKEN_WORD);
        j = 0;
      }
      buff[j++] = input[i++];
      while(input[i] != '\0' && input[i] != quout_char)
      {

          buff[j++] = input[i++];
      }
      if(input[i] == '\0')
      {
        printf("syntax error\n");
        NULL;
      }
      // if(input[i] != '\0')
      else
        buff[j++] = input[i++];
      buff[j] = '\0';
      stripped = strip_quotes(buff);  // remove quets from the buff before add token
      if(stripped != NULL && *stripped != '\0') // ensure ttripped not NULL or empty
      {
        add_token(&tokens, stripped, TOKEN_WORD);
        free(stripped);
      }
      j = 0;
      quout_char = 0;
    }
    else if(input[i] == ' ')
    {
      if(j > 0)  // if buffer has word save it
      {
        buff[j] = '\0';
        add_token(&tokens, buff, TOKEN_WORD);
        j = 0;
      }
      i++;
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
      i++;
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
      i += 2;
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
      i += 2;
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
      i++;
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
      i++;
    }
    else
    {
      buff[j++] = input[i++];  // if normal character add them to the buffer
      continue;
    }
  }
  if( j > 0)
  {
    buff[j] = '\0';
    add_token(&tokens, buff, TOKEN_WORD);
  }
  return (tokens);
}

// void print_tokens( t_token *tokens) // print tokens
// {
//   while(tokens != NULL)
//   {
//     printf("token => [%s], type => [%d]\n ", tokens->value, tokens->type);
//     tokens = tokens->next;
//   }
// }


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
//     char *input = "ls -la";

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

// int main()
// {
//     // char *input = "\"ls\" > out";
//     // char *input = "\"\"\"ls -la\"\"\"";
//     // char *input = "\"\'ls -la\'\"";
//     // char *input = "\'\'ls -la\'\'";
//     // char *input = "echo \"hello\"";
//     // char *input = "\"ls\" -lla > out";
//     // char *input = "\echo -ls\" \"  \"";
//     char *input = "\"echo hello\"\"";



//     // char *input = """";


//     // For debugging, print the actual raw input
//     printf("Raw input: %s\n", input);
//     for (int i = 0; input[i] != '\0'; i++) {
//         printf("%c[%d] ", input[i], input[i]);
//     }
//     printf("\n\n");
//     fflush(stdout);
//     // Tokenize the input
//     t_token *tokens = tokenize(input);

//     // Print the tokens with a clear separation
//     printf("---------------------------------\n");
//     printf("Tokens from tokenization:\n");
//     printf("---------------------------------\n");
//     print_tokens(tokens);
//     printf("---------------------------------\n");

//     // Rest of your code as before
//     t_command *commands = pars_tokens(tokens);
//     t_command *pipe_node = find_pipe_node(commands);

//     printf("\nParsed Commands:\n");
//     print_commands(commands);

//     if (pipe_node)
//         printf("Found a pipe node in the command list!\n");
//     else
//         printf("No pipe node found in the command list.\n");

//     return 0;
// }

