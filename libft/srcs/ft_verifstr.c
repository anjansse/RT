/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisnumber.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 22:17:03 by anjansse          #+#    #+#             */
/*   Updated: 2019/09/24 22:48:19 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_verifstr(char *str, char *allowed)
{
	size_t		i;
	size_t		j;
	int			verif;

	i = -1;
	while (++i < ft_strlen(str))
	{
		j = -1;
		verif = 0;
		while (++j < ft_strlen(allowed))
		{
			if (str[i] == allowed[j])
				verif = 1;
		}
		if (verif == 0)
			return (0);
	}
	return (1);
}
