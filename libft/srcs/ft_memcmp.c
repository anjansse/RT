/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 10:01:37 by anjansse          #+#    #+#             */
/*   Updated: 2018/11/29 12:00:13 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;

	if (!n)
		return (0);
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (--n > 0 && *p1 == *p2)
	{
		p1++;
		p2++;
	}
	return (*p1 - *p2);
}
