/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 20:31:34 by anjansse          #+#    #+#             */
/*   Updated: 2018/12/04 20:31:40 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int		vaend(int end)
{
	if (end < 0)
		end *= -1;
	return (end);
}

static int		vastart(int start)
{
	if (start < 0)
		start *= -1;
	return (start);
}

int				*ft_range(int start, int end)
{
	int length;
	int *array;
	int i;

	length = (vastart(start) + vaend(end));
	i = length;
	array = malloc(sizeof(int) * length);
	while (i > 0)
	{
		array[i] = end;
		end--;
		i--;
	}
	return (array);
}
