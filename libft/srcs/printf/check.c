/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:40:03 by anjansse          #+#    #+#             */
/*   Updated: 2019/02/26 11:21:59 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			check_flags(char c)
{
	char	*flags;
	int		i;

	i = 0;
	flags = "-+0 #";
	while (i < 5)
	{
		if (c == flags[i])
			return (1);
		i++;
	}
	return (0);
}

int			check_width(char c)
{
	if ((c >= '0' && c <= '9') || c == '*')
		return (1);
	return (0);
}

int			check_prec(char c)
{
	if (c == '.')
		return (1);
	return (0);
}

int			check_length(char c)
{
	char	*length;
	int		i;

	i = 0;
	length = "Llh";
	while (i < 3)
	{
		if (c == length[i])
			return (1);
		i++;
	}
	return (0);
}

int			check_specs(char c)
{
	char	*specifier;
	int		i;

	i = 0;
	specifier = "diouxXbfcsp%";
	while (i < 12)
	{
		if (c == specifier[i])
			return (1);
		i++;
	}
	return (0);
}
