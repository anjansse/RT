/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 13:39:07 by anjansse          #+#    #+#             */
/*   Updated: 2018/12/03 22:52:07 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char			*new;
	int				x;
	unsigned int	i;

	if (!s)
		return (NULL);
	i = 0;
	while ((s[i] == ' ') || (s[i] == '\t') || (s[i] == '\n'))
		i++;
	x = i;
	if (s[x] == '\0')
	{
		new = (char *)malloc(1);
		*new = '\0';
		return (new);
	}
	while (s[i + 1])
		i++;
	while ((s[i] == ' ') || (s[i] == '\t') || (s[i] == '\n'))
		i--;
	if (!(new = (ft_strsub(s, x, i - x + 1))))
		return (NULL);
	return (new);
}
