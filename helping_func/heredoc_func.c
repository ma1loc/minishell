# include "mini_shell.h"

void	heredoc_counter_in_pipe(t_setup *setup, t_tree *tree)
{
    if (tree->left)
		heredoc_counter(setup, tree->left);
    if (tree->right)
		heredoc_counter(setup, tree->right);
}

void	heredoc_counter(t_setup *setup, t_tree *tree)
{
    t_redirections	*redir;

	redir = tree->redirections;
    if (!tree)
		return ;
	
    if (tree->cmd && tree->cmd->redirections)
    {
        while (redir)
        {
            if (redir->type == TOKEN_HERDOC)
                setup->heredoc_counter++;
            redir = redir->next;
        }
    }
	heredoc_counter_in_pipe(setup, tree);
}