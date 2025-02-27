/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:36:43 by yanflous          #+#    #+#             */
/*   Updated: 2024/11/08 18:04:41 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell/mini_shell.h"

char	*ft_strdup(char *s1)
{
	char	*dup;
	size_t	s_len;
	size_t	i;

	s_len = ft_strlen(s1);
	dup = malloc(sizeof(char) * (s_len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s_len > i)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
