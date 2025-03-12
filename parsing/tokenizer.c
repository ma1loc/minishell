#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// char *strip_quotes(char *str) // func remove quotes for str  my func
// {
//   char *rslt;
//   int len;
//   int i;
//   int j;
//   char quoest_type;

//   if(!str)
//     return (NULL);
//   len = strlen(str);
//   rslt = malloc(len + 1);
//   if(!rslt)
//     return (NULL);
//   i = 0;
//   j = 0;
//   if(len > 0 && (str[0] == '"' || str[0] == '\''))   // identify outer quote type (first character)
//     quoest_type = str[0];
//   else
//     quoest_type = 0;
//   while(i < len)
//   {
//     if(str[i] == quoest_type && ( i == 0 || i == len - 1))    // only strip quotes that match the outer quote type and are at the beginning or end
//     {
//         //skeep this character
//     }
//     else
//     {
//       rslt[j] = str[i];
//       j++;
//     }
//     i++;
//   }
//   rslt[j] = '\0';
//   if(j == 0 && (quoest_type == '"' || quoest_type == '\''))
//     return(rslt);
//   if(j == 0)  // ensure that not return empy string
//   {
//     // printf("strip_quotes: empty string detected\n");  // debugging msg
//     free(rslt);
//     return(NULL);
//   }
//   return(rslt);
// }


char *strip_quotes(char *str)  //test
{
    char *result;
    int len;
    int i, j;
    int in_dquote = 0;
    int in_squote = 0;

    if (!str)
        return NULL;

    len = strlen(str);
    result = malloc(len + 1);
    if (!result)
        return NULL;

    i = 0;  // index for original string
    j = 0;  // index for result string

    // Process the string character by character
    while (i < len)
    {
        if (str[i] == '"' && !in_squote)
        {
            // Toggle double quote state if not inside single quotes
            in_dquote = !in_dquote;
        }
        else if (str[i] == '\'' && !in_dquote)
        {
            // Toggle single quote state if not inside double quotes
            in_squote = !in_squote;
        }
        else
        {
            // Copy any character that's not an opening/closing quote
            result[j++] = str[i];
        }
        i++;
    }

    result[j] = '\0';

    // If the result is empty but the original wasn't just quotes
    // (like for "" or '' or ""), return an empty string
    if (j == 0 && len > 0)
        return result;

    // For truly empty input
    if (j == 0 && len == 0)
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

  i = 0;
  in_quoets = 0;
  quoest_char = 0;

  while(input[i] != '\0')
  {
    if((input[i] == '"' || input[i] == '\'') && (quoest_char == input[i] || in_quoets == 0))
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


// t_token *tokenize(char *input)
// {
//   t_token *tokens = NULL;
//   char buff[1024];
//   int i = 0;
//   int j = 0;
//   char quote_char = 0;

//   if(!input)
//     return NULL;
//   if(check_quotes_syntax(input) != 0)
//     return NULL;

//   while(input[i] != '\0')
//   {
//     // Handle quoted text
//     if((input[i] == '"' || input[i] == '\'') && quote_char == 0)
//     {
//       // If we have content in the buffer, add it as a token
//       if(j > 0)
//       {
//         buff[j] = '\0';
//         add_token(&tokens, buff, TOKEN_WORD);
//         j = 0;
//       }

//       // Start the new token with the opening quote
//       quote_char = input[i];
//       buff[j++] = input[i++];

//       // Copy everything inside the quotes
//       while(input[i] != '\0' && input[i] != quote_char)
//       {
//         buff[j++] = input[i++];
//       }

//       // Handle the closing quote if present
//       if(input[i] == '\0')
//       {
//         printf("syntax error\n");
//         return NULL;
//       }
//       buff[j++] = input[i++]; // Add closing quote

//       // Important: After a quoted string, continue collecting characters
//       // until we hit a space or special character
//       while(input[i] != '\0' && input[i] != ' ' &&
//             input[i] != '|' && input[i] != '<' && input[i] != '>')
//       {
//         // If we encounter another quote, process it
//         if((input[i] == '"' || input[i] == '\''))
//         {
//           quote_char = input[i];
//           buff[j++] = input[i++];

//           while(input[i] != '\0' && input[i] != quote_char)
//           {
//             buff[j++] = input[i++];
//           }

//           if(input[i] == '\0')
//           {
//             printf("syntax error\n");
//             return NULL;
//           }
//           buff[j++] = input[i++]; // Add closing quote
//           quote_char = 0;
//         }
//         else
//         {
//           // Regular character
//           buff[j++] = input[i++];
//         }
//       }

//       // Now save the complete token
//       buff[j] = '\0';
//       char *stripped = strip_quotes(buff);
//       printf("buff --->%s\n", buff);
//       if(stripped != NULL && *stripped != '\0')
//       {
//         add_token(&tokens, stripped, TOKEN_WORD);
//         free(stripped);
//       }
//       j = 0;
//       quote_char = 0;
//     }
//     else if(input[i] == ' ')
//     {
//       if(j > 0)
//       {
//         buff[j] = '\0';
//         add_token(&tokens, buff, TOKEN_WORD);
//         j = 0;
//       }
//       i++;
//     }
//     else if(input[i] == '|')
//     {
//       if(j > 0)
//       {
//         buff[j] = '\0';
//         add_token(&tokens, buff, TOKEN_WORD);
//         j = 0;
//       }
//       buff[0] = '|';
//       buff[1] = '\0';
//       add_token(&tokens, buff, TOKEN_PIPE);
//       i++;
//     }
//     // Handle other special characters (>, >>, <, <<) as before
//     else if(input[i] == '>' && input[i + 1] == '>')
//     {
//       if(j > 0)
//       {
//         buff[j] = '\0';
//         add_token(&tokens, buff, TOKEN_WORD);
//         j = 0;
//       }
//       buff[0] = '>';
//       buff[1] = '>';
//       buff[2] = '\0';
//       add_token(&tokens, buff, TOKEN_APPEND);
//       i += 2;
//     }
//     else if(input[i] == '<' && input[i + 1] == '<')
//     {
//       if(j > 0)
//       {
//         buff[j] = '\0';
//         add_token(&tokens, buff, TOKEN_WORD);
//         j = 0;
//       }
//       buff[0] = '<';
//       buff[1] = '<';
//       buff[2] = '\0';
//       add_token(&tokens, buff, TOKEN_HERDOC);
//       i += 2;
//     }
//     else if(input[i] == '<')
//     {
//       if(j > 0)
//       {
//         buff[j] = '\0';
//         add_token(&tokens, buff, TOKEN_WORD);
//         j = 0;
//       }
//       buff[0] = '<';
//       buff[1] = '\0';
//       add_token(&tokens, buff, TOKEN_RED_IN);
//       i++;
//     }
//     else if(input[i] == '>')
//     {
//       if(j > 0)
//       {
//         buff[j] = '\0';
//         add_token(&tokens, buff, TOKEN_WORD);
//         j = 0;
//       }
//       buff[0] = '>';
//       buff[1] = '\0';
//       add_token(&tokens, buff, TOKEN_RED_OUT);
//       i++;
//     }
//     else
//     {
//       buff[j++] = input[i++];
//     }
//   }

//   // Don't forget any remaining text
//   if(j > 0)
//   {
//     buff[j] = '\0';
//     add_token(&tokens, buff, TOKEN_WORD);
//   }

//   return tokens;
// }


t_token *tokenize(char *input)
{
  t_token *tokens = NULL;
  char buff[1024];
  int i = 0;
  int j = 0;
  // int in_word = 0;

  if(!input)
    return NULL;
  if(check_quotes_syntax(input) != 0)
    return NULL;

  while(input[i] != '\0')
  {
    // Skip spaces between tokens
    if(input[i] == ' ')
    {
      if(j > 0)
      {
        // End of a word token
        buff[j] = '\0';
        char *stripped = strip_quotes(buff);
        if(stripped != NULL)
        {
          add_token(&tokens, stripped, TOKEN_WORD);
          free(stripped);
        }
        j = 0;
        // in_word = 0;
      }
      i++;
      continue;
    }

    // Handle special tokens (pipe, redirections)
    if(input[i] == '|' || input[i] == '<' || input[i] == '>')
    {
      // Save any buffered word first
      if(j > 0)
      {
        buff[j] = '\0';
        char *stripped = strip_quotes(buff);
        if(stripped != NULL)
        {
          add_token(&tokens, stripped, TOKEN_WORD);
          free(stripped);
        }
        j = 0;
        // in_word = 0;
      }

      // Handle the special token
      if(input[i] == '|')
      {
        add_token(&tokens, "|", TOKEN_PIPE);
        i++;
      }
      else if(input[i] == '>' && input[i + 1] == '>')
      {
        add_token(&tokens, ">>", TOKEN_APPEND);
        i += 2;
      }
      else if(input[i] == '<' && input[i + 1] == '<')
      {
        add_token(&tokens, "<<", TOKEN_HERDOC);
        i += 2;
      }
      else if(input[i] == '>')
      {
        add_token(&tokens, ">", TOKEN_RED_OUT);
        i++;
      }
      else if(input[i] == '<')
      {
        add_token(&tokens, "<", TOKEN_RED_IN);
        i++;
      }
      continue;
    }

    // We're now processing a word token (could contain quotes)
    // in_word = 1;

    // Handle quoted sections within a word
    if(input[i] == '"' || input[i] == '\'')
    {
      char quote_char = input[i];
      buff[j++] = input[i++]; // Add opening quote

      // Copy everything inside quotes
      while(input[i] != '\0' && input[i] != quote_char)
      {
        buff[j++] = input[i++];
      }

      if(input[i] == '\0')
      {
        printf("syntax error\n");
        return NULL;
      }

      buff[j++] = input[i++]; // Add closing quote
    }
    else
    {
      // Just a regular character in a word
      buff[j++] = input[i++];
    }
  }

  // Don't forget any remaining text in the buffer
  if(j > 0)
  {
    buff[j] = '\0';
    char *stripped = strip_quotes(buff);
    if(stripped != NULL)
    {
      add_token(&tokens, stripped, TOKEN_WORD);
      free(stripped);
    }
  }

  return tokens;
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




// int main()
// {
//     char *input = "echo \"hello\"";

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

