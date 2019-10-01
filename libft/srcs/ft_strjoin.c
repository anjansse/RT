/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 13:22:22 by anjansse          #+#    #+#             */
/*   Updated: 2018/12/03 21:37:53 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char *joinstr;

	if (!s1 || !s2)
		return (NULL);
	if (!(joinstr = (char *)malloc(ft_strlen((char *)s1) +
					ft_strlen((char *)s2) + 1)))
		return (NULL);
	joinstr = ft_strcpy(joinstr, (char *)s1);
	joinstr = ft_strcat(joinstr, (char *)s2);
	return (joinstr);
}
