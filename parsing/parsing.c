#include "tokenizer.h"
#include "../srcs/mini_shell.h"

t_redirections *new_redirection(char *file_name, t_token_type type)
{
  t_redirections *redir;
  redir = malloc(sizeof(t_redirections));
  if(!redir)
    return(NULL);
  if(file_name != NULL)
    redir->file_name = strdup(file_name);
  else
    redir->file_name = NULL;
  redir->type = type;
  redir->next = NULL;
  return(redir);
}
void add_redirection_to_list( t_command *cmd, char *file_name, t_token_type type)
{
  t_redirections *current_redir;
  t_redirections *new_redir;
  if(!cmd)
    return;
  new_redir = new_redirection(file_name, type);
  if(!new_redir)
    return;
  if(!cmd->redirections)
  {
    cmd->redirections = new_redir;
    return;
  }
  current_redir = cmd->redirections;
  while(current_redir->next != NULL)
  {
    current_redir = current_redir->next;
  }
  current_redir->next = new_redir;
  // new_redir->next = NULL;
}

void free_redirections(t_redirections *redir)
{
  t_redirections *current_redir;
  t_redirections *next_redir;

  current_redir = redir;
  while(current_redir != NULL)
  {
    next_redir = current_redir->next;
    free(current_redir->file_name);
    free(current_redir);
    current_redir = next_redir;
  }
}

t_command *pars_tokens(t_token *tokens)
{
  t_command *commandes;
  t_command *current_cmd; // track current commande
  t_command *new_cmd;
  t_token *current;
  t_args_list *list_args;
  int args_count;

  list_args = NULL;
  commandes = malloc(sizeof(t_command)); // creat new commande

  commandes->name = NULL;
  commandes->args = NULL;
  // commandes->input_file = NULL;
  // commandes->output_file = NULL;
  commandes->redirections = NULL;
  commandes->type = 0;
  commandes->next = NULL;

  current_cmd = commandes;
  current = tokens; // linked list of tokens
  args_count = 0;
  if(current == NULL)
    return NULL;
  while(current != NULL) // go trought each token
  {
    if(current->type == TOKEN_WORD)  // if first token is word
    {
      if(current_cmd->name == NULL && current->value[0] != '\0')
        current_cmd->name = strdup(current->value);  // first word become the first command name
      else
        add_args_to_list(&list_args, current);
    }
    else if(current->type == TOKEN_PIPE)
    {
      // current_cmd->type = current->type;
      if(list_args != NULL)
      {
        args_count = count_args_list(list_args);
        current_cmd->args = malloc((args_count + 2) * sizeof(char *));
        fill_array(list_args, current_cmd);

        current_cmd->args[args_count + 1] = NULL;
        // free_list_args(list_args);
        list_args = NULL;
      }
      else
      {
        current_cmd->args = malloc(sizeof(char *)); // if no args for this command
        current_cmd->args[0] = NULL;
      }
      new_cmd = malloc(sizeof(t_command));
      new_cmd->name = strdup("|");
      new_cmd->args = NULL;
      new_cmd->redirections = NULL;
      new_cmd->type = TOKEN_PIPE;
      new_cmd->next = NULL;

      current_cmd->next = new_cmd;  // link the pip node
      current_cmd = new_cmd;
      // list_args = NULL;
      new_cmd = malloc(sizeof(t_command));
      if(!new_cmd)  // creat new node for the next commande
        return(NULL);
      new_cmd->name = NULL;
      new_cmd->args = NULL;
      new_cmd->redirections = NULL;
      new_cmd->type = 0;
      new_cmd->next = NULL;

      current_cmd->next = new_cmd;
      current_cmd = new_cmd;

    }
    else if(current->type == TOKEN_RED_IN || current->type == TOKEN_HERDOC)
    {
      if(current->next && current->next->type == TOKEN_WORD) // next token shoud be the input filename
      {
        add_redirection_to_list(current_cmd, current->next->value, current->type);
        current = current->next; // skip filename token
      }
    }
    else if(current->type == TOKEN_RED_OUT || current->type == TOKEN_APPEND)
    {
      if(current->next && current->next->type == TOKEN_WORD)
      {
        // current_cmd->output_file = strdup(current->next->value);
        // current_cmd->type = current->type;
        add_redirection_to_list(current_cmd, current->next->value, current->type);
        current = current->next;
      }
    }
    current = current->next;
  }

  if(list_args != NULL)  // process argus for last command
  {
    args_count = count_args_list(list_args);
    current_cmd->args = malloc((args_count + 2) * sizeof(char *));
    if (!current_cmd->args)
      return NULL;

    fill_array(list_args, current_cmd);

    current_cmd->args[args_count + 1] = NULL;
    // free_list_args(list_args);
    list_args = NULL;
  }
  else if (current_cmd->args == NULL)
  {
      current_cmd->args = malloc(2 * sizeof(char *));
      if (!current_cmd->args)
          return NULL;
      if (current_cmd->name)  // Add this check
          current_cmd->args[0] = strdup(current_cmd->name);
      else
          current_cmd->args[0] = NULL;
      current_cmd->args[1] = NULL;
      // Don't call fill_array here since list_args is NULL
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

//         // Print redirections with their types
//         if (current->input_file)
//             printf("  Input Redirection (<): %s\n", current->input_file);

//         if (current->output_file) {
//             // Check type of output redirection
//             if (current->type == 5) // For >>
//                 printf("  Output Redirection (>>): %s\n", current->output_file);
//             else if (current->type == 3) // For > (assuming type 3)
//                 printf("  Output Redirection (>): %s\n", current->output_file);
//             else
//                 printf("  Output Redirection (type %d): %s\n", current->type, current->output_file);
//         }

//         // Check for pipe
//         if (current->type == 2) // Pipe is type 2
//             printf("  Piped to next command (|)\n");

//         printf("\n");
//         current = current->next;
//         cmd_num++;
//     }
// }

//

// void print_commands(t_command *commands)
// {
//     t_command *current = commands;
//     int cmd_num = 1;

//     if (!commands) {
//         printf("No commands to print\n");
//         return;
//     }

//     while (current) {
//         printf("Command %d:\n", cmd_num);

//         // Print command type with better clarity
//         printf("  Type: ");
//         if (current->type == TOKEN_WORD)
//             printf("WORD\n");
//         else if (current->type == TOKEN_PIPE)
//             printf("PIPE (command followed by pipe)\n");
//         else if (current->type == TOKEN_RED_IN)
//             printf("REDIRECT_IN\n");
//         else if (current->type == TOKEN_RED_OUT)
//             printf("REDIRECT_OUT\n");
//         else if (current->type == TOKEN_APPEND)
//             printf("REDIRECT_APPEND\n");
//         else if (current->type == TOKEN_HERDOC)
//             printf("HEREDOC\n");
//         else if (current->type == 0)
//             printf("SIMPLE (end of pipeline)\n");
//         else
//             printf("UNKNOWN (%d)\n", current->type);

//         // Print command name
//         printf("  Name: %s\n", current->name ? current->name : "NULL");

//         // Print arguments
//         printf("  Arguments:");
//         if (current->args) {
//             int i = 0;
//             while (current->args[i]) {
//                 printf(" %s", current->args[i]);
//                 i++;
//             }
//             printf("\n");
//         } else {
//             printf(" (none)\n");
//         }

//         // Print redirections
//         printf("  Redirections:\n");
//         if (current->redirections) {
//             t_redirections *redir = current->redirections;
//             int redir_num = 1;

//             while (redir) {
//                 printf("    Redirection %d: ", redir_num);

//                 // Check for NULL file_name
//                 const char *filename = redir->file_name ? redir->file_name : "NULL";

//                 if (redir->type == TOKEN_RED_IN)
//                     printf("Input from '%s'\n", filename);
//                 else if (redir->type == TOKEN_RED_OUT)
//                     printf("Output to '%s'\n", filename);
//                 else if (redir->type == TOKEN_APPEND)
//                     printf("Append to '%s'\n", filename);
//                 else if (redir->type == TOKEN_HERDOC)
//                     printf("herdoc to '%s'\n", filename);
//                 else
//                     printf("Unknown type %d, file: '%s'\n", redir->type, filename);

//                 redir = redir->next;
//                 redir_num++;
//             }
//         } else {
//             printf("    None\n");
//         }

//         // Check for pipe
//         if (current->type == TOKEN_PIPE)
//             printf("  Piped to next command\n");

//         printf("\n");
//         current = current->next;
//         cmd_num++;
//     }
// }


t_args_list *add_args_to_list(t_args_list **list_head, t_token *token)
{
  t_args_list *current_arg;
  t_args_list *new_arg;

  if(!token || !token->value)
    return(NULL);
  new_arg = malloc(sizeof(t_args_list));
  if(!new_arg)
  {
    // free other stuf
    return (NULL);
  }
  new_arg->value = strdup(token->value);
  new_arg->type = token->type;
  new_arg->next = NULL;

  if(*list_head == NULL)
  {
    *list_head = new_arg;
    return(new_arg);
  }
  current_arg = *list_head;
  while(current_arg->next != NULL)
  {
    current_arg = current_arg->next;
  }
  current_arg->next = new_arg;
  return(new_arg);
}

int count_args_list(t_args_list *args)
{
  t_args_list *tmp;
  int i;

  tmp = args;
  i = 0;
  while(tmp != NULL)
  {
    i++;
    tmp = tmp->next;
  }
  return(i);
}

void fill_array(t_args_list *list, t_command *cmd)
{
    t_args_list *current;
    char combined_args[1024] = {0};

    // current = NULL;
    int i = 0;
    current = list;
    if(!current)
      return;
    if(!cmd || !cmd->name)
      return;
    cmd->args[i++] = strdup(cmd->name);
    if(current != NULL && strcmp(current->value, cmd->name) == 0)
      current = current->next;
    while (current != NULL )
    {
        if((current->value[0] == '"' || current->value[0] == '\'') && (strlen(current->value) == 1) && current->next && (current->next->value[0] == '"' || current->next->value[0] == '\'') && strlen(current->next->value) == 1)
        {
          strcpy(combined_args, current->value);
          strcat(combined_args, current->next->value);
          cmd->args[i++] = strdup(combined_args);
          current = current->next->next;  // Skip the next token since we've already used it
        }
        else
        {
          cmd->args[i++] = strdup(current->value);
          current = current->next;
        }
    }
    cmd->args[i] = NULL;
}


// void free_list_args(t_args_list *list_args)
// {
//   t_args_list *tmp;

//   while(list_args != NULL)
//   {
//     tmp = list_args;
//     list_args = list_args->next;
//     free(tmp->value);
//     free(tmp);
//   }

// }





