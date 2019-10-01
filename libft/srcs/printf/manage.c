/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 23:16:06 by anjansse          #+#    #+#             */
/*   Updated: 2019/02/19 00:36:05 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static t_answer			*otherother_manage_specs(t_answer *ret, t_arg *key,
		char *str)
{
	if (str[key->specs_pos[0]] == 'X')
		ret->type = "X";
	else if (str[key->specs_pos[0]] == 'p')
		ret->type = "p";
	else if (str[key->specs_pos[0]] == 'f')
		ret->type = "f";
	return (ret);
}

static t_answer			*other_manage_specs(t_answer *ret, t_arg *key,
		char *str)
{
	if (str[key->specs_pos[0]] == 'u')
		ret->type = "uint";
	else if (str[key->specs_pos[0]] == 'o')
		ret->type = "octal";
	else if (str[key->specs_pos[0]] == 'x')
		ret->type = "x";
	else if (str[key->specs_pos[0]] == 'b')
		ret->type = "b";
	return (ret = otherother_manage_specs(ret, key, str));
}

static t_answer			*manage_specs(t_answer *ret, t_arg *key, char *str)
{
	if (str[key->specs_pos[0]] == 'd' || str[key->specs_pos[0]] == 'i')
		ret->type = "int";
	else if (str[key->specs_pos[0]] == 's')
		ret->type = "char*";
	else if (str[key->specs_pos[0]] == 'c')
		ret->type = "char";
	else if (str[key->specs_pos[0]] == '%')
		ret->type = "percentage";
	return (ret = other_manage_specs(ret, key, str));
}

static t_answer			*manage_length(t_answer *ret, t_arg *key, char *str)
{
	if (str[key->length_pos[0]] == 'h' && str[(key->length_pos[0] + 1)] == 'h')
		ret->length = "hh";
	else if (str[key->length_pos[0]] == 'h' &&
			str[(key->length_pos[0] + 1)] != 'h')
		ret->length = "h";
	else if (str[key->length_pos[0]] == 'l' &&
			str[key->length_pos[0] + 1] == 'l')
		ret->length = "ll";
	else if (str[key->length_pos[0]] == 'l' &&
			str[(key->length_pos[0] + 1)] != 'l')
		ret->length = "l";
	else if (str[key->length_pos[0]] == 'L')
		ret->length = "L";
	return (ret);
}

t_answer				*apply_argument(t_answer *ret, t_arg *key, char *str,
		va_list list)
{
	if (key->flags == 1)
		ret = manage_flags(ret, key, str);
	if (key->width == 1)
		ret = get_width(ret, key, str, list);
	if (key->prec == 1)
		ret = manage_prec(ret, key, str, list);
	if (key->length == 1)
		ret = manage_length(ret, key, str);
	if (key->specs == 1)
		ret = manage_specs(ret, key, str);
	return (ret);
}
