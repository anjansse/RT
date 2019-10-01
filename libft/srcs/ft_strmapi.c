/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 11:22:22 by anjansse          #+#    #+#             */
/*   Updated: 2018/12/02 23:18:29 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
			newstr[x] = (*f)(x, s[x]);
			x++;
		}
		newstr[x] = '\0';
		return (newstr);
	}
	return (0);
}
