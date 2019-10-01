/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 17:32:40 by anjansse          #+#    #+#             */
/*   Updated: 2018/11/30 09:25:55 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t x;

	x = 0;
	c = ((unsigned char)c);
	while (x < len)
	{
		((unsigned char *)b)[x] = ((unsigned char)c);
		x++;
	}
	return (b);
}
