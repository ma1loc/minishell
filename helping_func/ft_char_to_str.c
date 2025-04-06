#include "mini_shell.h"

char *char_to_str(char c)
{
	char	*str;

    str = malloc(2);
    if (!str)
        return (NULL);
    str[0] = c;
    str[1] = '\0';
    return (str);
}