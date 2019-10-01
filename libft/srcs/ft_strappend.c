/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 13:10:48 by anjansse          #+#    #+#             */
/*   Updated: 2019/02/28 13:10:57 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strappend(char *str, char c)
{
	char	*new;
	int		i;

	i = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i++] = c;
	new[i] = '\0';
	ft_strdel(&str);
	return (new);
}
