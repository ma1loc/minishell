/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 09:10:00 by yanflous          #+#    #+#             */
/*   Updated: 2025/02/02 09:10:02 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	delim_count(char *str, char separator)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == separator)
			i++;
		if (str[i] && str[i] != separator)
			count++;
		while (str[i] && str[i] != separator)
			i++;
	}
	return (count);
}

char	*get_the_word(char *str, int *index, char separator)
{
	int		start;
	char	*word;
	int		count;
	int		i;

	start = *index;
	count = 0;
	while (str[start] && str[start] == separator)
		start++;
	*index = start;
	while (str[*index] && str[*index] != separator)
	{
		(*index)++;
		count++;
	}
	word = gc_malloc(gc, sizeof(char) * (count + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < count)
	{
		word[i] = str[start + i];
		i++;
	}
	return (word[i] = '\0', word);
}

char	**ft_split(char *str, char separator)
{
	char	**new_str;
	int		word_count;
	int		index;
	int		i;

	if (!str)
		return (NULL);
	word_count = delim_count(str, separator);
	new_str = gc_malloc(gc, sizeof(char *) * (word_count + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	index = 0;
	while (i < word_count)
	{
		new_str[i] = get_the_word(str, &index, separator);
		if (!new_str[i])
			return (NULL);
		i++;
	}
	return (new_str[i] = NULL, new_str);
}
