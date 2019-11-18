/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verifstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 22:17:03 by anjansse          #+#    #+#             */
/*   Updated: 2019/11/17 13:50:18 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ----------------------------------------------------------------------------
** Takes a string and verifies each character to see if doesn't contain invalid
** ones.
**
** @param {char *} str - String to verify.
** @param {char *} allowed - Allowed characters in string.
** ----------------------------------------------------------------------------
*/

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
