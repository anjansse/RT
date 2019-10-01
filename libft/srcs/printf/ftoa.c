/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 12:25:37 by anjansse          #+#    #+#             */
/*   Updated: 2019/02/21 14:02:11 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include <stdio.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

static uint64_t					power_to(uint64_t n, int width)
{
	int							ten;

	ten = 10;
	while (width > 0)
	{
		n *= ten;
		width--;
	}
	return (n);
}

static int						is_neg(long double n)
{
	if (n < 0)
		return (1);
	return (0);
}

static int						ndigit(uint64_t n)
{
	int							len;

	len = 0;
	while (n / 10)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static int						get_f_size(long double n, int width, int which)
{
	int							tmp;
	uint64_t					tmp2;
	int							len1;
	int							len2;

	len1 = 0;
	len2 = 0;
	if (is_neg(n))
	{
		len1++;
		n *= -1;
	}
	tmp = (int)n;
	n = n - tmp;
	len1 = ndigit(tmp);
	tmp2 = (uint64_t)(n * power_to(1, width));
	len2 = ndigit(tmp2 + 0.5);
	return (which == 2 ? len2 + 1 : len1 + 2);
}

char							*ft_ftoa(long double n, int width)
{
	int							sign;
	int							tmp;
	char						*str1;
	char						*str2;
	char						*str3;

	str3 = (char *)ft_memalloc(sizeof(char) * (get_f_size(n, width, 1) +
				get_f_size(n, width, 2)) + 1);
	str2 = (char *)ft_memalloc(sizeof(char) * get_f_size(n, width, 2) + 1);
	str1 = (char *)ft_memalloc(sizeof(char) * get_f_size(n, width, 1) + 1);
	sign = is_neg(n) ? -1 : 1;
	if (n < 0)
		n *= -1;
	tmp = (int)n;
	str1 = ft_itoa(tmp);
	if (((n - tmp) * power_to(1, width)) == 0)
		str2 = append_zero(width);
	else
		str2 = ft_iitoa(((n - tmp) * power_to(1, width) + 0.5));
	str2 = ft_strjoin(".", str2);
	str3 = ft_strjoin(str1, str2);
	if (sign == 0)
		str3 = ft_strjoin("-", str3);
	return (str3);
}
