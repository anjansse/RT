/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:54:57 by anjansse          #+#    #+#             */
/*   Updated: 2019/11/16 22:43:17 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		isnumber(char *n)
{
	int i;

	i = 0;
	while (n[i])
	{
		if ((n[i] >= '0' && n[i] <= '9') || n[i] == '-')
			++i;
		else
			send_error("Invalid input (number contains invalid char).\n");
	}
}

int				ft_stoi(char *n)
{
	int		r;
	int		sign;

	isnumber(n);
	r = 0;
	sign = 1;
	while (*n == ' ' || *n == '\t' || *n == '\v' || *n == '\n' || *n == '\r'\
			|| *n == '\f')
		n++;
	if (*n == '-')
		sign = -1;
	if (*n == '-' || *n == '+')
		n++;
	while (*n >= '0' && *n <= '9')
	{
		r = r * 10 + (*n - '0');
		n++;
	}
	return (r * sign);
}
