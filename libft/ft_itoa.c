/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:47:37 by yanflous          #+#    #+#             */
/*   Updated: 2024/11/05 20:19:38 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_shell.h"

static int	nbr_len(int n)
{
	size_t			n_len;
	unsigned int	nbr;

	n_len = 0;
	if (n <= 0)
		n_len = 1;
	if (n < 0)
		nbr = -n;
	else
		nbr = n;
	while (nbr > 0)
	{
		nbr = nbr / 10;
		n_len++;
	}
	return (n_len);
}

static char	*is_zero(char *ptr)
{
	ptr[0] = '0';
	return (ptr);
}

char	*ft_itoa(int n, t_gc *gc)
{
	size_t			n_len;
	char			*ptr;
	unsigned int	nbr;

	n_len = nbr_len(n);
	ptr = gc_malloc(gc, sizeof(char) * (n_len + 1));
	if (!ptr)
		return (NULL);
	ptr[n_len] = '\0';
	if (n == 0)
		return (is_zero(ptr));
	if (n < 0)
	{
		nbr = -n;
		ptr[0] = '-';
	}
	else
		nbr = n;
	while (nbr > 0)
	{
		--n_len;
		ptr[n_len] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	return (ptr);
}
