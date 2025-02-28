/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:11:52 by yanflous          #+#    #+#             */
/*   Updated: 2024/12/02 09:44:51 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/mini_shell.h"

static int	ft_fscheck(va_list arg, char c)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_putchar(va_arg(arg, int));
	else if (c == 's')
		count += ft_putstr(va_arg(arg, char *));
	else if (c == 'd' || c == 'i')
		count += ft_putnbr(va_arg(arg, int));
	else if (c == 'x' || c == 'X')
		count += ft_puthex(va_arg(arg, unsigned int), c);
	else if (c == 'u')
		count += ft_putuint(va_arg(arg, unsigned int));
	else if (c == 'p')
		count += ft_putadd(va_arg(arg, void *));
	else
		count += ft_putchar(c);
	return (count);
}

int	ft_printf(const char *s, ...)
{
	va_list	arg;
	int		count;
	int		i;

	if (s == NULL)
		return (-1);
	va_start(arg, s);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			if (s[i] == '\0')
				return (-1);
			count += ft_fscheck(arg, s[i]);
		}
		else
			count += ft_putchar(s[i]);
		i++;
	}
	va_end(arg);
	return (count);
}
