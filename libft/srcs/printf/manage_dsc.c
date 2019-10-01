/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 12:08:49 by anjansse          #+#    #+#             */
/*   Updated: 2019/02/21 13:50:20 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static char		*check_null(va_list list)
{
	char	*null;

	null = va_arg(list, char *);
	if (null == NULL)
	{
		null = "(null)";
		return (null);
	}
	return (null);
}

static void		apply_eos(t_answer *ret, int size)
{
	int		i;

	i = 0;
	if (ret->minus == 0)
	{
		while (i < size)
		{
			write(1, &ret->res[i], 1);
			i++;
		}
		ft_strdel(&ret->res);
	}
	else if (ret->minus == 1)
	{
		ft_putchar(0);
		ft_putstr(ret->res);
		ft_strdel(&ret->res);
	}
}

void			manage_d(t_answer *ret, t_arg *key, va_list list)
{
	if (key->length == 1)
	{
		if (ft_strequ(ret->length, "h"))
			ret->res = ft_iitoa((short int)va_arg(list, int64_t));
		else if (ft_strequ(ret->length, "hh"))
			ret->res = ft_iitoa((signed char)va_arg(list, int64_t));
		else if (ft_strequ(ret->length, "l"))
			ret->res = ft_iitoa((long int)va_arg(list, int64_t));
		else if (ft_strequ(ret->length, "ll"))
			ret->res = ft_iitoa(va_arg(list, long long int));
	}
	else if (key->length == 0)
		ret->res = ft_itoa(va_arg(list, int));
	if (key->prec == 1)
		ret = minimum_dig(ret);
	if (key->width == 1 || key->flags == 1)
		ret = add_width(ret, key);
	key->tot += get_ps(ret->res);
	ft_strdel(&ret->res);
}

void			manage_s(t_answer *ret, t_arg *key, va_list list)
{
	if (key->specs == 1)
		ret->res = check_null(list);
	if (key->prec == 1)
		ret = prec_handle(ret);
	if (key->width == 1 || key->flags == 1)
		ret = add_width(ret, key);
	key->tot += get_ps(ret->res);
}

void			manage_c(t_answer *ret, t_arg *key, va_list list)
{
	int			size;
	int			i;

	i = 0;
	if (key->specs == 1)
		ret->res = ft_cs(ret, va_arg(list, int));
	if (key->prec == 1)
		ret = prec_handle(ret);
	if (key->width == 1 || key->flags == 1)
		ret = add_width(ret, key);
	if (ret->eos == 1)
	{
		size = ft_strlen(ret->res) + 1;
		apply_eos(ret, size);
		key->tot += size;
	}
	else if (ret->eos == 0)
	{
		key->tot += get_ps(ret->res);
		ft_strdel(&ret->res);
	}
}
