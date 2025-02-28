/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:51:31 by yanflous          #+#    #+#             */
/*   Updated: 2024/11/26 09:34:01 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/mini_shell.h"

int	ft_puthex(unsigned int n, char c)
{
	char	*hex_based;
	int		count;

	count = 0;
	if (c == 'x')
		hex_based = "0123456789abcdef";
	if (c == 'X')
		hex_based = "0123456789ABCDEF";
	if (n <= 15)
		count += ft_putchar(hex_based[n]);
	else
	{
		count += ft_puthex(n / 16, c);
		count += ft_puthex(n % 16, c);
	}
	return (count);
}
