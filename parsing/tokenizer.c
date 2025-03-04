#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_token *add_token( t_token **head, char *value, t_token_type type) // function creat new token and add it to the lincked list
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
        add_token(&tokens, buff, TOKEN_PIPE);
        j = 0;
      }
      buff[0] = '|';
      buff[1] = '\0';
      add_token(&tokens, buff, TOKEN_PIPE);
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
    else if(input[i] == '>' && input[i + 1] == '>')
    {
      if(j > 0)
      {
        buff[j] = '\0';
        add_token(tokens, buff, TOKEN_APPEND);
      }
      buff[0] = '>';
      buff[1] = '>';
      buff[2] = '\0';
      add_token(tokens, buff, TOKEN_APPEND);
    }
    else if(input[i] == '<' && input[i + 1] == '<')
    {
      if(j > 0)
      {
        buff[j] = '\0';
        add_token(tokens, buff, TOKEN_HERDOC);
      }
      buff[0] = '<';
      buff[1] = '<';
      buff[2] = '\0';
      add_token(tokens, buff, TOKEN_HERDOC);
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
    printf("token =>[%s]type =>[%d] ", tokens->value, tokens->type);
    tokens = tokens->next;
  }
}

void free_tokens(t_token *tokens) // fix it to free leaKS
{
  t_token *current;
  t_token *next;

  current = tokens;
  while(current)
  {
    next = current->next;
    free(current->value);  // free string
    free(current);         // free token struct
    current = current->next;
  }
}



int main()
{
  char *input = "ls -l | grep test >> out.txt";
  t_token *tokens = tokenize(input);
  print_tokens(tokens);
  free_tokens(tokens);
}

