/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_uox.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 11:45:11 by anjansse          #+#    #+#             */
/*   Updated: 2019/02/26 12:41:31 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static t_answer		*other_mox(t_answer *ret, t_arg *key, int base[2])
{
	if (key->prec == 1)
		ret = minimum_dig(ret);
	if (ret->hash == 1 && ret->zero != '0')
		ret->res = is_hash(ret, key, base[0], base[1]);
	ret = (key->width == 1 || key->flags == 1) ? add_width(ret, key) : ret;
	if (ret->hash == 1 && ret->zero == '0')
		ret->res = is_hash(ret, key, base[0], base[1]);
	if (ret->hash == 1 && ft_strequ(ret->type, "b"))
		ret->res = is_hash(ret, key, base[0], base[1]);
	return (ret);
}

void				manage_u(t_answer *ret, t_arg *key, va_list list)
{
	if (key->length == 1)
	{
		if (ft_strequ(ret->length, "h"))
			ret->res = ft_itoa_base((unsigned short int)
					va_arg(list, uint64_t), 10, 0);
		else if (ft_strequ(ret->length, "hh"))
			ret->res = ft_itoa_base((unsigned char)
					va_arg(list, uint64_t), 10, 0);
		else if (ft_strequ(ret->length, "l"))
			ret->res = ft_itoa_base((unsigned long int)
					va_arg(list, uint64_t), 10, 0);
		else if (ft_strequ(ret->length, "ll"))
			ret->res = ft_itoa_base((unsigned long long int)
					va_arg(list, uint64_t), 10, 0);
	}
	else if (key->length == 0)
		ret->res = ft_itoa_base((unsigned int)
				va_arg(list, uint64_t), 10, 0);
	if (key->prec == 1)
		ret = minimum_dig(ret);
	if (key->width == 1)
		ret = add_width(ret, key);
	key->tot += get_ps(ret->res);
	ft_strdel(&ret->res);
}

void				manage_ox(t_answer *ret, t_arg *key, va_list list,
		int base[2])
{
	if (key->length == 1)
	{
		if (ft_strequ(ret->length, "h"))
			ret->res = ft_itoa_base((unsigned short int)
						va_arg(list, uint64_t), base[0], base[1]);
		else if (ft_strequ(ret->length, "hh"))
			ret->res = ft_itoa_base((unsigned char)
						va_arg(list, uint64_t), base[0], base[1]);
		else if (ft_strequ(ret->length, "l"))
			ret->res = ft_itoa_base((unsigned long int)
						va_arg(list, uint64_t), base[0], base[1]);
		else if (ft_strequ(ret->length, "ll"))
			ret->res = ft_itoa_base((unsigned long long int)
						va_arg(list, uint64_t), base[0], base[1]);
	}
	else if (key->length == 0)
		ret->res = ft_itoa_base((unsigned int)
				va_arg(list, uint64_t), base[0], base[1]);
	ret = other_mox(ret, key, base);
	key->tot += get_ps(ret->res);
	ft_strdel(&ret->res);
}
