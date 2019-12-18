/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:54:59 by anjansse          #+#    #+#             */
/*   Updated: 2019/12/17 18:56:03 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		handle_precision(float *rez, float *fact, char *s)
{
	int		d;
	int		point_seen;

	point_seen = 0;
	while (*s)
	{
		if (*s == '.')
			point_seen = 1;
		else
		{
			d = *s - '0';
			if (d >= 0 && d <= 9)
			{
				if (point_seen)
					*fact /= 10.0f;
				*rez = *rez * 10.0f + (float)d;
			}
		}
		s++;
	}
}

float			ft_stof(char *s)
{
	float	rez;
	float	fact;

	fact = 1;
	rez = 0;
	if (*s == '-')
	{
		s++;
		fact = -1;
	}
	handle_precision(&rez, &fact, s);
	return (rez * fact);
}
