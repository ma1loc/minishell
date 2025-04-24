/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:04:23 by yanflous          #+#    #+#             */
/*   Updated: 2024/11/02 18:54:22 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*ft_strchr(char *s, int c)
{
	size_t	i;
	char	ch;

	i = 0;
	ch = (char)c;
	if (!s[i])
		return (NULL);
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *) s + i);
		i++;
	}
	if (ch == '\0')
		return ((char *) s + i);
	return (NULL);
}
