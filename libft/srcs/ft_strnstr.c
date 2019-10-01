/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:50:25 by anjansse          #+#    #+#             */
/*   Updated: 2018/11/29 12:04:29 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t		x;
	unsigned	a;

	x = 0;
	if (!*s2)
		return ((char *)s1);
	while (s1[x])
	{
		a = 0;
		while (s1[x] == s2[a] && s1[x] && x < n)
		{
			a++;
			x++;
		}
		if (!s2[a])
			return ((char *)&s1[x - a]);
		x = (x - a) + 1;
	}
	return (NULL);
}
