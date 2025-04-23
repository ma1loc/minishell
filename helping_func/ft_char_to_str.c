/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:58:43 by yanflous          #+#    #+#             */
/*   Updated: 2025/04/23 09:58:47 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*char_to_str(char c)
{
	char	*str;

	str = gc_malloc(g_gc, 2);
	if (!str)
		allocation_failed_msg();
	str[0] = c;
	str[1] = '\0';
	return (str);
}
