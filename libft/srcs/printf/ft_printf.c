/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 12:20:24 by anjansse          #+#    #+#             */
/*   Updated: 2019/02/21 13:23:11 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int				ft_printf(const char *format, ...)
{
	va_list		arg_list;
	int			res;
	char		*str;
	t_arg		*key;
	t_answer	*ret;

	key = (t_arg *)malloc(sizeof(t_arg));
	ret = (t_answer *)malloc(sizeof(t_answer));
	initiate_values(ret, key);
	str = ft_strdup(format);
	va_start(arg_list, format);
	res = parse_it(ret, key, str, arg_list);
	va_end(arg_list);
	free(str);
	free(key);
	free(ret);
	return (res);
}
