#include "mini_shell.h"

void	unset_key(t_setup *setup, char *key)
{
	t_env	*curr;
	t_env	*prev;

	if (!setup->env || !key)
		return ;
	curr = setup->env;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev == NULL)	// >>> but this condition what is the time to be ture
                setup->env = curr->next;
            else
                prev->next = curr->next;
            free(curr->key);
            if (curr->value)
                free(curr->value);
            free(curr);
            return ;
        }
        prev = curr;
        curr = curr->next;
	}
}

// >>> reomve the key, value from the env.
void	unset_cmd(t_setup *setup)
{
    char	**args;
    int		i;

	i = 1;	// skip the command itself
	args = setup->cmd->args;	// >>> just to be readable

    if (!args || !args[1])		// >>> here the args alrady include the command itself (i think i have to remove it!!! (no need for the !args check))
		return (setup->exit_stat = 0, (void)0);

    while (args[i])
    {
		if (!is_valid_identifier(args[i]))
		{
			i++;
			continue ;
		}
        unset_key(setup, args[i]);
		i++;
    }
	setup->exit_stat = 0; // what ever if the unset fail or not will return 0 in the exit status
}
