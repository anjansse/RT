/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 16:25:48 by anjansse          #+#    #+#             */
/*   Updated: 2018/11/29 12:04:36 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s1, int c)
{
	int x;

	x = ft_strlen((char *)s1);
	while (s1[x])
		x++;
	while (x > 0 && s1[x] != (char)c)
		x--;
	if (s1[x] == (char)c)
		return ((char *)&s1[x]);
	return (NULL);
}
