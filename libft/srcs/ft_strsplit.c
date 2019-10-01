/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 21:12:27 by anjansse          #+#    #+#             */
/*   Updated: 2018/12/03 22:50:18 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_place_words(char const *s, char c, int *newi)
{
	int		i;
	int		begin;
	char	*word;

	i = 0;
	while (s[*newi] == c && s[*newi] != '\0')
		(*newi)++;
	begin = *newi;
	while (s[*newi] != c && s[*newi] != '\0')
		(*newi)++;
	if (!(word = ft_strnew(*newi - begin)))
		return (NULL);
	while (begin < *newi)
		word[i++] = s[begin++];
	word[i] = '\0';
	return (word);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**strings;
	int		i;
	int		count;
	int		k;

	k = 0;
	count = 0;
	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	i = 0;
	if (!(strings = (char **)malloc((count + 1) * sizeof(char *))))
		return (NULL);
	while (i < count)
		strings[i++] = ft_place_words(s, c, &k);
	strings[i] = 0;
	return (strings);
}
