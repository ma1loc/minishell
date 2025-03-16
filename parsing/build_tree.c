#include "tokenizer.h"
#include "../srcs/mini_shell.h"

t_tree *build_tree_commande(t_command *commandes)
{
  t_command *pip_cmd;
  t_command *prev_cmd;
  t_tree *leaf;
  t_tree *root;
  t_command *right_cmds;

  if(!commandes)
    return(NULL);
  pip_cmd = commandes;   // commande to store pip commande later
  prev_cmd = NULL;

  while(pip_cmd != NULL && pip_cmd->type != TOKEN_PIPE)  // ls | cat | wc
  {
    prev_cmd = pip_cmd;
    pip_cmd = pip_cmd->next;
  }

  if(pip_cmd == NULL)  // if pip command not foumd
  {
    leaf = malloc(sizeof(t_tree));
    if(!leaf)
      return(NULL);
    if(commandes->name != NULL)
      leaf->name = strdup(commandes->name);
    else
      leaf->name = NULL;
    leaf->type = TOKEN_WORD;
    leaf->args = commandes->args;
    leaf->cmd = commandes;
    leaf->redirections = commandes->redirections;
    leaf->left = NULL;
    leaf->right = NULL;
    return(leaf);
  }
  right_cmds = pip_cmd->next;
  root = malloc(sizeof(t_tree));  // root |
  if(!root)
    return NULL;
  root->name = NULL;
  root->args = NULL;
  root->redirections = NULL;
  root->type = TOKEN_PIPE;
  root->cmd = pip_cmd;
  if(prev_cmd != NULL)
  {
    prev_cmd->next = NULL;
    root->left = (build_tree_commande(commandes));
  }
  else
    root->left = NULL; //edge case if pip is the first token

  ////
  if(right_cmds != NULL)
    root->right = (build_tree_commande(right_cmds));
  else
    root->right = NULL;
    ////?
  return(root);
  }
