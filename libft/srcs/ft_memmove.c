/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 19:38:05 by anjansse          #+#    #+#             */
/*   Updated: 2018/12/03 13:09:43 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t x;

	if (len == 0)
		return (dst);
	if (dst > src)
	{
		x = len;
		while (x > 0)
		{
			x--;
			((char *)dst)[x] = ((char *)src)[x];
		}
	}
	else
	{
		x = 0;
		while (x < len)
		{
			((char *)dst)[x] = ((char *)src)[x];
			x++;
		}
	}
	return (dst);
}
