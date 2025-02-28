/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:22:39 by yanflous          #+#    #+#             */
/*   Updated: 2024/11/26 09:24:22 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell/mini_shell.h"


int	ft_putnbr(int nbr)
{
	char	c;
	int		count;

	count = 0;
	if (nbr == -2147483648)
	{
		count = ft_putstr("-2147483648");
		return (count);
	}
	if (nbr < 0)
	{
		count += ft_putchar('-');
		nbr = -nbr;
	}
	if (nbr <= 9)
	{
		c = (nbr + '0');
		count += ft_putchar(c);
	}
	else
	{
		count += ft_putnbr(nbr / 10);
		count += ft_putnbr(nbr % 10);
	}
	return (count);
}
