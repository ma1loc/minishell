#include "mini_shell.h"

int is_valid_number(char *str)
{
    int i;

    i = 0;
    if (str[0] == '-' || str[0] == '+')
        i++;

    if (!str[i])
        return (0);

    if (ft_isdigit(str + i) == 0)
        return (0);

    return (1);
}

int is_valid_identifier(char *key)
{
	int i;
	
	if (!key || !*key)
		return (0);

	// >>> check the first char in the "key"
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	
	// >>> loop the the remaining char can be num, alpha, or '_'
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void free_the_spliting(char **split)
{
    int i;
    
    i = 0;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}

void free_env_list(t_env *env_list)
{
    t_env *current;
    t_env *next;
    
    current = env_list;
    while (current)
    {
        next = current->next;
        if (current->key)
            free(current->key);
        if (current->value)
            free(current->value);
        free(current);
        current = next;
    }
}
