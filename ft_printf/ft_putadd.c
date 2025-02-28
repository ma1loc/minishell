/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:48:20 by yanflous          #+#    #+#             */
/*   Updated: 2024/12/02 09:30:14 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell/mini_shell.h"

static	int	puthex(unsigned long n)
{
	int		count;
	char	*hex_based;

	count = 0;
	hex_based = "0123456789abcdef";
	if (n <= 15)
		count += ft_putchar(hex_based[n]);
	else
	{
		count += puthex(n / 16);
		count += puthex(n % 16);
	}
	return (count);
}

int	ft_putadd(void *ptr)
{
	unsigned long	add;
	int				count;

	count = 0;
	if (!ptr)
		return (ft_putstr("(nil)"));
	add = (unsigned long)ptr;
	count += ft_putstr("0x");
	count += puthex(add);
	return (count);
}
