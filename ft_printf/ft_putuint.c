/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:20:46 by yanflous          #+#    #+#             */
/*   Updated: 2024/11/26 09:22:11 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell/mini_shell.h"


int	ft_putuint(unsigned int n)
{
	char	c;
	int		count;

	count = 0;
	if (n <= 9)
	{
		c = (n + '0');
		count += ft_putchar(c);
	}
	else
	{
		count += ft_putuint(n / 10);
		count += ft_putuint(n % 10);
	}
	return (count);
}
