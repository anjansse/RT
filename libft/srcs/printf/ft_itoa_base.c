/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 15:07:25 by anjansse          #+#    #+#             */
/*   Updated: 2019/02/26 11:22:51 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char						*ft_strrev(char *str, int len)
{
	int						i;
	int						j;
	char					t;

	i = 0;
	j = len - 1;
	while (j > i)
	{
		t = str[i];
		str[i] = str[j];
		str[j] = t;
		j--;
		i++;
	}
	return (str);
}

static char					conv_n(int n, int cap)
{
	if (n == 10)
		return (cap == 1 ? 'A' : 'a');
	if (n == 11)
		return (cap == 1 ? 'B' : 'b');
	if (n == 12)
		return (cap == 1 ? 'C' : 'c');
	if (n == 13)
		return (cap == 1 ? 'D' : 'd');
	if (n == 14)
		return (cap == 1 ? 'E' : 'e');
	if (n == 15)
		return (cap == 1 ? 'F' : 'f');
	return (0);
}

static int					get_future_size(uint64_t n, int base)
{
	unsigned long long		rest;
	unsigned long long		i;
	int						x;

	rest = 0;
	i = 1;
	x = 0;
	while (n > 0)
	{
		rest += ((n % base) * i);
		n = (n - (n % base)) / base;
		i *= 10;
		x++;
	}
	return (x);
}

char						*ft_itoa_base(uint64_t value, int base, int cap)
{
	int						x;
	char					*number;
	int						len;

	if (value == 0)
	{
		number = ft_itoa(0);
		return (number);
	}
	len = get_future_size(value, base);
	number = (char *)malloc(sizeof(char) * len + 1);
	x = 0;
	while (value > 0)
	{
		if ((value % base) <= 9)
			number[x] = ((value % base) + '0');
		if ((value % base) > 9)
			number[x] = conv_n((value % base), cap);
		value = (value - (value % base)) / base;
		x++;
	}
	number = ft_strrev(number, len);
	number[x] = '\0';
	return (number);
}
