/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 10:35:39 by anjansse          #+#    #+#             */
/*   Updated: 2018/11/29 12:02:43 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		x;
	int		a;
	char	*tmp;

	a = 0;
	while (s1[a])
		a++;
	if (!(tmp = (char *)malloc(sizeof(*tmp) * (a + 1))))
		return (NULL);
	x = 0;
	while (s1[x] != '\0')
	{
		tmp[x] = s1[x];
		x++;
	}
	tmp[x] = '\0';
	return (tmp);
}
