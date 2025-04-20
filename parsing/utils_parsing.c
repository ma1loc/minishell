#include "../srcs/mini_shell.h"
#include "tokenizer.h"

static int	count_numbers(int n)
{
	int				count;
	unsigned int	num;

	num = n;
	count = 0;
	if (n < 0)
	{
		num = -n;
		count++;
	}
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num = num / 10;
		count++;
	}
	return (count);
}

static char	*fill_ptr(int num, char *ptr)
{
	if (num == 0)
	{
		ptr[0] = '0';
		ptr[1] = '\0';
	}
	return (ptr);
}

char	*ft_itoa_(int n)
{
	size_t			num_len;
	unsigned int	num;
	char			*ptr;

	num_len = count_numbers(n);
	ptr = malloc(sizeof(char) * (num_len + 1));
	if (!ptr)
		return (NULL);
	if (n < 0)
	{
		num = -n;
		ptr[0] = '-';
	}
	else
		num = n;
	fill_ptr(num, ptr);
	if (num > 0)
		ptr[num_len] = '\0';
	while (num > 0)
	{
		ptr[--num_len] = (num % 10) + '0';
		num = num / 10;
	}
	return (ptr);
}
static void	cpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

char	*ft_strjoin_(char *s1, char *s2)
{
	size_t	total_len;
	char	*ptr;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (NULL);
	if (!s2)
		return (strdup(s1));
	total_len = ft_strlen(s1) + ft_strlen(s2);
	ptr = malloc(sizeof(char) * (total_len + 1));
	if (!ptr)
		return (NULL);
	cpy(ptr, s1);
	cpy(ptr + ft_strlen(s1), s2);
	return (ptr);
}
