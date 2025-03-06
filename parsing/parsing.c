#include "tokenizer.h"
#include "../srcs/mini_shell.h"

t_command *pars_tokens(t_token *tokens)
{
  t_command *commandes;
  t_command *current_cmd; // track current commande
  t_command *new_cmd;
  t_token *current;
  int args_count;

  commandes = malloc(sizeof(t_command)); // creat new commande
  commandes->name = NULL;
  commandes->args = malloc(10 * sizeof(char *));
  commandes->args[0] = NULL;
  commandes->input_file = NULL;
  commandes->output_file = NULL;
  // commandes->piped = 0;
  commandes->next = NULL;
  current_cmd = commandes;
  current = tokens; // linked list of tokens
  args_count = 0;
  while(current != NULL) // go trought each token
  {
    if(current->type == TOKEN_WORD)  // if first token is word
    {
      if(current_cmd->name == NULL)
        current_cmd->name = strdup(current->value);  // first word become the first command name
      current_cmd->args[args_count] = strdup(current->value);     // cuurent_comd for the commandes and current for tokens
      args_count++;
      current_cmd->args[args_count] = NULL;     // set the next arg to NULL
    }
    else if(current->type == TOKEN_PIPE)
    {
      current_cmd->type = current->type;
      new_cmd = malloc(sizeof(t_command));
      new_cmd->name = NULL;
      new_cmd->args = malloc(10 * sizeof(char *));
      new_cmd->args[0] = NULL;
      new_cmd->input_file = NULL;
      new_cmd->output_file = NULL;
      current_cmd->next = new_cmd; // link current command to the new command
      current_cmd = new_cmd; // move to the new command
      new_cmd->next = NULL;
      args_count = 0;
    }
    else if(current->type == TOKEN_RED_IN)
    {
      if(current->next && current->next->type == TOKEN_WORD) // next token shoud be the input filename
      {
        current_cmd->input_file = strdup(current->next->value);
        current = current->next; // skip filename token
      }
    }
    else if(current->type == TOKEN_RED_OUT)
    {
      if(current->next && current->next->type == TOKEN_WORD)
      {
        current_cmd->output_file = strdup(current->next->value);
        current = current->next;
      }
    }
    else if (current->type == TOKEN_APPEND)
    {
      if(current_cmd == NULL)
        current_cmd->name = strdup(current->value);
      current_cmd->args[args_count] = strdup(current->value);
      args_count++;
      current_cmd->args[args_count] = NULL;
    }
    current = current->next;
  }
  return(commandes);
}

// void print_commands(t_command *commands)
// {
//     t_command *current = commands;
//     int cmd_num = 1;

//     while (current) {
//         printf("Command %d:\n", cmd_num);

//         // Print command name
//         printf("  Name: %s\n", current->name ? current->name : "NULL");

//         // Print arguments
//         printf("  Arguments:");
//         if (current->args && current->args[0]) {
//             for (int i = 0; current->args[i] != NULL; i++) {
//                 printf(" %s", current->args[i]);
//             }
//             printf("\n");
//         } else {
//             printf(" (none)\n");
//         }

//         // Print redirections
//         if (current->input_file)
//             printf("  Input File: %s\n", current->input_file);
//         if (current->output_file)
//             printf("  Output File: %s\n", current->output_file);

//         // Check for pipeline if `type` field exists
//         // (Assuming you added `type` to `t_command` structure)
//         if (current->type == TOKEN_PIPE)
//             printf("  Piped to next command\n");

//         printf("\n"); // Better spacing between commands
//         current = current->next;
//         cmd_num++;
//     }
// }
