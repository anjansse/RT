/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 20:48:18 by anjansse          #+#    #+#             */
/*   Updated: 2019/06/13 11:24:57 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void					initiate_values(t_answer *ret, t_arg *key)
{
	ret->eos = 0;
	key->tot = 0;
	key->specs = 0;
	key->length = 0;
	key->width = 0;
	key->prec = 0;
	key->flags = 0;
	ret->minus = 0;
	ret->width = 0;
	ret->prec = 6;
	ret->plus = 0;
	ret->space = 0;
	ret->hash = 0;
	ret->zero = ' ';
	ret->res = NULL;
	ret->length = NULL;
	ret->type = NULL;
}

static int				go_end_arg(char *str, int x)
{
	if (check_flags(str[x]))
		while (check_flags(str[x]) == 1)
			x++;
	if (check_width(str[x]))
		while (check_width(str[x]) == 1)
			x++;
	if (check_prec(str[x]))
		while (check_width(str[++x]) == 1)
			x++;
	if (check_length(str[x]))
		while (check_length(str[x]) == 1)
			x++;
	if (check_specs(str[x]))
		while (check_specs(str[x]) == 1)
			x++;
	return (x - 1);
}

static int				is_legal(char c)
{
	char				*list;
	int					i;

	i = 0;
	list = "*diouxXbfcspLlh-+0123456789. #%";
	while (list[i])
	{
		if (c == list[i])
			return (1);
		i++;
	}
	return (0);
}

static t_arg			*parse(t_arg *key, char *str, int x)
{
	if (str[x])
	{
		ft_putchar(str[x]);
		key->tot++;
	}
	return (key);
}

int						parse_it(t_answer *ret, t_arg *key, char *str,
		va_list list)
{
	int					x;

	x = 0;
	while (str[x])
	{
		initiate_values(ret, key);
		if (str[x + 1] && str[x] == '%')
		{
			x++;
			if (str[x] && is_legal(str[x]))
			{
				key = create_key(key, str, x);
				handle(apply_argument(ret, key, str, list), key, list);
				if (str[x + 1] && str[x + 1] != '%')
					x = go_end_arg(str, x);
			}
			else
				key = parse(key, str, x);
		}
		else
			key = parse(key, str, x);
		x++;
	}
	return (key->tot);
}
