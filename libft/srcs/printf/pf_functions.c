/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 13:55:07 by anjansse          #+#    #+#             */
/*   Updated: 2019/02/28 12:55:26 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

char						*ft_cs(t_answer *ret, char c)
{
	char					*str;

	str = (char *)malloc(sizeof(char) + 1);
	if (c == 0)
	{
		ret->eos = 1;
		*str = 0;
		return (str);
	}
	*str = c;
	return (str);
}

t_answer					*get_width(t_answer *ret, t_arg *key, char *str,
		va_list list)
{
	char					*number;
	int						len;
	int						x;
	int						y;

	if (str[key->width_pos[0]] == '*')
	{
		ret->width = (int)va_arg(list, int64_t);
		return (ret);
	}
	x = 0;
	y = key->width_pos[0];
	len = key->width_pos[1] - y;
	number = (char *)ft_memalloc(sizeof(char) * len + 1);
	while (x < len)
		number[x++] = str[y++];
	number[x] = '\0';
	ret->width = ft_atoi(number);
	free(number);
	return (ret);
}

int							diff_w(t_answer *ret, char *str, int w)
{
	int						res;
	int						len;

	len = ft_strlen(str);
	if (ret->hash == 1 && ret->zero == '0')
		w -= 2;
	if (w <= len)
		return (res = 0);
	if (ret->res[0] == '-' && ret->zero == '0')
		return (((len - w) * -1) + 1);
	else if (ret->eos == 1)
		return (((len - w) * -1) - 1);
	else
		return ((len - w) * -1);
	return (0);
}

t_answer					*add_width(t_answer *ret, t_arg *key)
{
	int						i;
	int						len;
	char					*zero;

	ret = (key->flags == 1 && key->width == 0) ? apply_flag(ret) : ret;
	len = diff_w(ret, ret->res, ret->width);
	zero = (char *)ft_memalloc(sizeof(char) * len + 1);
	i = 0;
	if (ret->zero == '0' && (ret->space == 1 ||
				ret->res[0] == '-' || ret->plus == 1))
	{
		ret = boycott_zero(ret);
		zero[i++] = ret->ex;
	}
	while (i < len)
	{
		zero[i] = ret->zero;
		i++;
	}
	if (ret->minus == 1)
		ret->res = pf_strjoinfree(ret->res, zero, ret, 0);
	else if (ret->minus == 0)
		ret->res = pf_strjoinfree(zero, ret->res, ret, 1);
	ft_strdel(&zero);
	return (ret);
}

char						*pf_address(unsigned int n, t_answer *ret)
{
	char					*str1;
	char					*str2;
	char					*str3;

	str1 = "0x7ffe";
	str2 = ft_itoa_base(n, 16, 0);
	str3 = pf_strjoinfree(str1, str2, ret, 1);
	return (str3);
}
