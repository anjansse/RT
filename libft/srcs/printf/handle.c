/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 17:08:16 by anjansse          #+#    #+#             */
/*   Updated: 2019/06/13 11:22:23 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_answer		*manage_prec(t_answer *ret, t_arg *key, char *str,
		va_list list)
{
	char	*number;
	int		len;
	int		x;
	int		y;

	if (str[key->prec_pos[0]] == '*')
	{
		ret->prec = (int)va_arg(list, int64_t);
		return (ret);
	}
	x = 0;
	y = key->prec_pos[0];
	len = key->prec_pos[1] - y;
	number = (char *)ft_memalloc(sizeof(char) * len + 1);
	while (x < len)
		number[x++] = str[y++];
	number[x] = '\0';
	ret->prec = ft_atoi(number);
	free(number);
	return (ret);
}

t_answer		*manage_flags(t_answer *ret, t_arg *key, char *str)
{
	int		i;

	i = key->flags_pos[0];
	while (i <= key->flags_pos[1])
	{
		if (str[i] == '-')
			ret->minus = 1;
		if (str[i] == '0' && key->prec == 0)
			ret->zero = '0';
		if (str[i] == ' ')
			ret->space = 1;
		if (str[i] == '+')
			ret->plus = 1;
		if (str[i] == '#')
			ret->hash = 1;
		i++;
	}
	return (ret);
}

static void		other_handle_base(t_answer *ret, t_arg *key, va_list list,
		int base[2])
{
	if (!(ft_strcmp(ret->type, "X")))
	{
		base[0] = 16;
		base[1] = 1;
		manage_ox(ret, key, list, base);
	}
	else if (!(ft_strcmp(ret->type, "b")))
	{
		base[0] = 2;
		base[1] = 0;
		manage_ox(ret, key, list, base);
	}
}

static void		handle_base(t_answer *ret, t_arg *key, va_list list)
{
	int base[2];

	if (!(ft_strcmp(ret->type, "octal")))
	{
		base[0] = 8;
		base[1] = 0;
		manage_ox(ret, key, list, base);
	}
	else if (!(ft_strcmp(ret->type, "x")))
	{
		base[0] = 16;
		base[1] = 0;
		manage_ox(ret, key, list, base);
	}
	else
		other_handle_base(ret, key, list, base);
}

void			handle(t_answer *ret, t_arg *key, va_list list)
{
	if (!(ft_strcmp(ret->type, "int")))
		manage_d(ret, key, list);
	else if (!(ft_strcmp(ret->type, "char*")))
		manage_s(ret, key, list);
	else if (!(ft_strcmp(ret->type, "char")))
		manage_c(ret, key, list);
	else if (!(ft_strcmp(ret->type, "percentage")))
		manage_per(ret, key);
	else if (!(ft_strcmp(ret->type, "uint")))
		manage_u(ret, key, list);
	else if (!(ft_strcmp(ret->type, "f")))
		manage_f(ret, key, list, ret->prec);
	else if (!(ft_strcmp(ret->type, "p")))
		manage_p(ret, key, list);
	else
		handle_base(ret, key, list);
}
