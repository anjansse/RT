/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:43:46 by anjansse          #+#    #+#             */
/*   Updated: 2018/11/30 09:31:40 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t x;

	x = 0;
	while (x < n)
	{
		if (((unsigned char *)src)[x] == (unsigned char)c)
		{
			((unsigned char *)dst)[x] = ((unsigned char *)src)[x];
			return (dst + x + 1);
		}
		((unsigned char *)dst)[x] = ((unsigned char *)src)[x];
		x++;
	}
	return (NULL);
}
