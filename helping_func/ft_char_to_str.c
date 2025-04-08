#include "mini_shell.h"

char *char_to_str(char c, t_gc *gc)
{
	char	*str;

    str = gc_malloc(gc, 2);
    if (!str)
        allocation_failed_msg(gc);
    str[0] = c;
    str[1] = '\0';
    return (str);
}
