/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 22:06:54 by anjansse          #+#    #+#             */
/*   Updated: 2018/12/03 21:10:18 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		sign;
	int		count;
	char	*str;

	count = 1;
	sign = n;
	while (sign /= 10)
		count++;
	sign = n < 0 ? 1 : 0;
	count = n < 0 ? count += 1 : count;
	if (n == -2147483648)
		return (str = ft_strdup("-2147483648"));
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
