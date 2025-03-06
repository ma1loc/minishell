#include "../srcs/mini_shell.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	char			*s;
	unsigned char	ch;

	s = (char *)str;
	ch = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		s[i] = ch;
		i++;
	}
	return (str);
}