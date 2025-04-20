/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:35:10 by yanflous          #+#    #+#             */
/*   Updated: 2024/11/05 15:13:31 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	mem_fill(char *str, char *ptr, size_t idx)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		ptr[idx] = str[i];
		idx++;
		i++;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	size_t	t_len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
	{
		ptr = ft_strdup(s2);
		return (ptr);
	}
	if (!s2)
	{
		ptr = ft_strdup(s1);
		return (ptr);
	}
	t_len = ft_strlen(s1) + ft_strlen(s2);
	ptr = gc_malloc(g_gc, sizeof(char) * (t_len + 1));
	if (!ptr)
		allocation_failed_msg();
	mem_fill(s1, ptr, 0);
	mem_fill(s2, ptr, ft_strlen(s1));
	ptr[t_len] = '\0';
	return (ptr);
}
