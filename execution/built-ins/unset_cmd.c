#include "../../srcs/mini_shell.h"

// >>> reomve the key, value from the env.
<<<<<<< HEAD
void	unset_cmd(t_env **env_list, char *key)
=======
<<<<<<< HEAD
void	unset_cmd(t_env **env_list, char *key)
=======
void	unset_env(t_env **env_list, char *key)
>>>>>>> 4b13520 (update)
>>>>>>> 0ce570e13e4b0b223063194c26e845647d18e9d8
{
    t_env	*current;
    t_env	*previous;

    if (!*env_list)
		return;
    current = *env_list;
    previous = NULL;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            if (previous == NULL)
                *env_list = current->next;
            else
                previous->next = current->next;
            free(current->key);
            free(current->value);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}