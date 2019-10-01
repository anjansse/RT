/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:56:03 by anjansse          #+#    #+#             */
/*   Updated: 2018/11/29 12:04:50 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int		x;
	int		a;
	char	*p1;
	char	*p2;

	x = 0;
	p1 = (char *)s1;
	p2 = (char *)s2;
	if (!*p2)
		return ((char *)p1);
	while (p1[x])
	{
		a = 0;
		while (p1[x] == p2[a] && p1[x])
		{
			++x;
			++a;
		}
		if (!p2[a])
			return (&((char *)p1)[x - a]);
		x = (x - a) + 1;
	}
	return (NULL);
}
