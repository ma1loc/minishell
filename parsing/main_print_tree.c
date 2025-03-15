#include "tokenizer.h"
#include "../srcs/mini_shell.h"


void print_command_list(t_command *cmd) {
  int i = 0;
  printf("Command list structure:\n");
  while (cmd) {
      // Check if this is a pipe command
      if (cmd->type == TOKEN_PIPE) {
          printf("[%d] Type: %d (PIPE), Name: %s\n",
                 i++,
                 cmd->type,
                 cmd->name ? cmd->name : "NULL");
      } else {
          printf("[%d] Type: %d (CMD), Name: %s\n",
                 i++,
                 cmd->type,
                 cmd->name ? cmd->name : "NULL");
      }

      if (cmd->args) {
          printf("    Args: ");
          int j = 0;
          while (cmd->args[j]) {
              printf("%s ", cmd->args[j]);
              j++;
          }
          printf("\n");
      }

      cmd = cmd->next;
  }
}


void print_tree(t_tree *root, int level)
{
  if (root == NULL)
  {
      printf("NULL node at level %d\n", level);
      return;
  }

  printf("Node at level %d: type=%d, name=%s\n",
         level,
         root->type,
         root->name ? root->name : "NULL");

    // Print indentation based on level
    int i = 0;
    while (i < level)
    {
        printf("  ");
        i++;
    }

    // Print node information
    if (root->type == TOKEN_PIPE)
    {
        printf("PIPE\n");
    }
    else
    {
        printf("CMD: %s\n", root->name ? root->name : "NULL");

        // Print arguments if any
        if (root->args != NULL)
        {
            i = 0;
            while (i < level + 1)
            {
                printf("  ");
                i++;
            }
            printf("Args: ");

            i = 0;
            while (root->args[i] != NULL)
            {
                printf("%s ", root->args[i]);
                i++;
            }
            printf("\n");
        }

        // Print redirections if any
        if (root->redirections != NULL)
        {
            t_redirections *redir = root->redirections;
            while (redir != NULL)
            {
                i = 0;
                while (i < level + 1)
                {
                    printf("  ");
                    i++;
                }

                if (redir->type == TOKEN_RED_IN)
                    printf("< %s\n", redir->file_name);
                else if (redir->type == TOKEN_RED_OUT)
                    printf("> %s\n", redir->file_name);
                else if (redir->type == TOKEN_APPEND)
                    printf(">> %s\n", redir->file_name);
                else if (redir->type == TOKEN_HERDOC)
                    printf("<< %s\n", redir->file_name);

                redir = redir->next;
            }
        }
    }

    // Recursively print left and right subtrees
    print_tree(root->left, level + 1);
    print_tree(root->right, level + 1);
}

// int main()
// {
//     // Example: ls -l | grep "file" > output.txt

//     // Create tokens manually or with your tokenizer
//     // t_token *tokens = tokenize("ls -l | grep \"file\" > output.txt");
//     t_token *tokens = tokenize("ls");


//     // Parse tokens into commands
//     t_command *commands = pars_tokens(tokens);

//     print_command_list(commands);
//     // Build the tree
//     t_tree *tree = build_tree_commande(commands);

//     // Print the tree
//     printf("Command Tree:\n");
//     print_tree(tree, 0);

//     // Note: You'll need to be careful about freeing memory later
//     // since multiple tree nodes may point to the same command data

//     return 0;
// }