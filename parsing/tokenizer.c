#include "tokenizer.h"
#include "../srcs/mini_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *strip_quotes(char *str)  //test
{
    char *result;
    int len;
    int i;
    int j;
    int in_dquote;
    int in_squote;

    in_dquote = 0;
    in_squote = 0;
    // if (!str)            // check this bsc i check it in the first input
    //     return NULL;
    len = strlen(str);
    result = malloc(len + 1);
    if (!result)
        return NULL;
    i = 0;  // index for original string
    j = 0;  // index for result string
    while (i < len)  // process the string character by character
    {
        if (str[i] == '"' && in_squote == 0)
        {
            if (in_dquote == 0)
                in_dquote = 1;   // now we are on duble
            else
                in_dquote = 0;
        }
        else if (str[i] == '\'' && in_dquote == 0)
        {
            if (in_squote == 0)
                in_squote = 1;  // now we're inside single quotes
            else
                in_squote = 0;  // now we're outside single quotes
        }
        else
            result[j++] = str[i];  // copy any character that's not an opening/closing quote
        i++;
    }
    result[j] = '\0';
    if (j == 0 && len > 0)  // If the result is empty but the original wasn't just quotes (like for "" or '' or ""), return an empty string
        return result;
    if (j == 0 && len == 0)   // For truly empty input
    {
        free(result);
        return NULL;
    }
    return result;
}


int check_quotes_syntax(char *input) // fuc to check if quoest match inclosed or no
{
  int i;
  int in_quoets;
  char quoest_char;
  char len;

  i = 0;
  in_quoets = 0;
  quoest_char = 0;
  len = strlen(input);
  while(input[i] != '\0')
  {
    if(input[0] == '|' || input[len - 1] == '|')
    {
      in_quoets = 1;
      break;
    }
    else if ((input[i] == '"' || input[i] == '\'') && (quoest_char == input[i] || in_quoets == 0))
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
   // ft_perror()   put later the msg and exit status with this func
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


t_token *tokenize(char *input)
{
  t_tokinizer_state *state;
  t_token *tokens;

  tokens = NULL;
  state = malloc(sizeof(t_tokinizer_state));
  if(!state)
    return NULL;
  state->i = 0;
  state->j = 0;
  memset(state->buff, 0, sizeof(state->buff));
  if(!input || check_quotes_syntax(input) != 0)
    return (free(state), NULL);
  while(input[state->i] != '\0')
  {
    if(input[state->i] == ' ')    // skip spaces between tokens
      process_spaces(state, &tokens);
    else if(input[state->i] == '|' || input[state->i] == '<' || input[state->i] == '>')  // Handle special tokens (pipe, redirections)
      process_special_tokens(input, state, &tokens);
    else if(input[state->i] == '"' || input[state->i] == '\'') // Handle quoted sections within a word
      process_quotes(input, state);
    else
      process_normal_word(input,state);  // just a regular character in a word
  }
  process_remainder_text(state, &tokens);  // don't forget any remaining text in the buffer
  return (free(state), tokens);
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




// int main() /////////////////////////////////////////////////
// {
//     // char *input = "echo        \"hello \'\'      \" \"world\"";
//     // char *input ="ls -la | cat | wc -l";
//     char *input = "<< ls cat echo walo";


//     printf("Raw input: %s\n", input);
//     printf("\n");
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

// int main(int argc , char **argv)
// {
//     // char *input = "\"ls\" > out";
//     // char *input = "\"\"\"ls -la\"\"\"";
//     // char *input = "\"\'ls -la\'\"";
//     // char *input = "\'\'ls -la\'\'";
//     // char *input = "echo \"hello\"";
//     // char *input = "echo \"\"\'\"\"\'\"\"\'\'";
//     // char *input = "\"ls\" -lla > out";
//     // char *input = "\echo -ls\" \"  \"";
//   // char *input = "echo \'\"\'\'\"\'";
//   char *input = "echo \"hello\"\" word\"";
//   // char *input = "echo \'\"\'";
//   // char *input = """";

//     // if (argc < 2)
//     // {
//     //     printf("Usage: %s \"command to tokenize\"\n", argv[0]);
//     //     printf("Example: %s \"ls -la | grep .c\"\n", argv[0]);
//     //     return 1;
//     // }
//     // // Use the first argument as input
//     // input = argv[1];
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
