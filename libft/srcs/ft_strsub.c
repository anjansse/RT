/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 11:53:19 by anjansse          #+#    #+#             */
/*   Updated: 2018/12/02 21:32:20 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t		x;
	char		*substr;

	x = 0;
	if (!s)
		return (0);
	if (!(substr = (char *)ft_memalloc(len + 1)))
		return (NULL);
	while (len > 0)
	{
		substr[x] = s[start];
		x++;
		start++;
		len--;
	}
	return (substr);
}
