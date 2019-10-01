/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 12:28:26 by anjansse          #+#    #+#             */
/*   Updated: 2019/02/23 13:03:57 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void			manage_f(t_answer *ret, t_arg *key, va_list list, int width)
{
	if (key->length == 1)
		ret->res = ft_ftoa(va_arg(list, long double), width);
	else if (key->length == 0)
		ret->res = ft_ftoa((double)va_arg(list, double), width);
	if (key->width == 1 || key->flags == 1)
		ret = add_width(ret, key);
	key->tot += get_ps(ret->res);
	ft_strdel(&ret->res);
}

void			manage_p(t_answer *ret, t_arg *key, va_list list)
{
	ret->res = pf_address((unsigned int)va_arg(list, void *), ret);
	if (key->width == 1 || key->flags == 1)
		ret = add_width(ret, key);
	key->tot += get_ps(ret->res);
	ft_strdel(&ret->res);
}

void			manage_per(t_answer *ret, t_arg *key)
{
	ret->res = "%";
	if (key->width == 1 || key->flags == 1)
		ret = add_width(ret, key);
	key->tot += get_ps(ret->res);
}
