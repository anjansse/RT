/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_ws.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 22:09:26 by anjansse          #+#    #+#             */
/*   Updated: 2019/06/13 23:07:29 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char			*skip_ws(char *str)
{
	int		i;
	int		j;
	char	*str2;

	i = 0;
	j = 0;
	str2 = ft_strnew(ft_strlen(str));
	while (str[i])
	{
		if (ft_isws(str[i]))
			i++;
		else
		{
			str2[j] = str[i];
			i++;
			j++;
		}
	}
	free(str);
	return (str2);
}
