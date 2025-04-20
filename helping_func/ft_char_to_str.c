#include "mini_shell.h"

char *char_to_str(char c)
{
	char	*str;

    str = gc_malloc(g_gc, 2);
    if (!str)
        allocation_failed_msg();
    str[0] = c;
    str[1] = '\0';
    return (str);
}
