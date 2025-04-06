# include "mini_shell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char *new;
	
	new = ft_strjoin(s1, s2);
	if (!new)
		return (NULL);
	free(s1);
	return (new);
}