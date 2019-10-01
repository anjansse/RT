/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 22:06:54 by anjansse          #+#    #+#             */
/*   Updated: 2019/02/26 11:22:10 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*ft_iitoa(int64_t n)
{
	int64_t		sign;
	int			count;
	char		*str;

	count = 1;
	sign = n;
	while (sign /= 10)
		count++;
	sign = n < 0 ? 1 : 0;
	count = n < 0 ? count += 1 : count;
	str = ft_strnew(count);
	if (!str)
		return (NULL);
	if (sign == 1)
		str[0] = '-';
	n = n < 0 ? n *= -1 : n;
	while (--count >= sign)
	{
		str[count] = n >= 10 ? (n % 10) + 48 : n + 48;
		n /= 10;
	}
	str[ft_strlen(str)] = '\0';
	return (str);
}
