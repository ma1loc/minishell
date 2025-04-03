#include "mini_shell.h"

int ft_isalnum(int c)
{
    return (ft_isalpha(c) || (c >= '0' && c <= '9'));
}
