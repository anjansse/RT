/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 10:52:41 by anjansse          #+#    #+#             */
/*   Updated: 2018/12/02 17:38:04 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*newstr;
	size_t	x;

	x = 0;
	if (!s || !f)
		return (NULL);
	newstr = (char *)malloc(ft_strlen(s) + 1);
	if (newstr)
	{
		while (x < ft_strlen(s))
		{
			newstr[x] = (*f)(s[x]);
			x++;
		}
		newstr[x] = '\0';
		return (newstr);
	}
	return (0);
}
