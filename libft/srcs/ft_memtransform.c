/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 11:19:17 by anjansse          #+#    #+#             */
/*   Updated: 2019/03/12 00:45:13 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

uint32_t		ft_memtransform(uint32_t dst, char *src, unsigned int start,
		int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		dst <<= 8;
		dst |= ((unsigned int)src[start]);
		ft_printf("C IS %x\n", src[start]);
		start++;
		i++;
	}
	return (dst);
}
