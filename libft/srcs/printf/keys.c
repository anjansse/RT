/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:20:39 by anjansse          #+#    #+#             */
/*   Updated: 2019/02/16 12:10:38 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_arg			*flags_key(t_arg *key, char *str, int beg)
{
	key->flags_pos[0] = beg;
	key->flags = 1;
	while (check_flags(str[beg]) == 1)
		beg++;
	key->flags_pos[1] = beg - 1;
	key->index = beg;
	return (key);
}

t_arg			*width_key(t_arg *key, char *str, int beg)
{
	key->width_pos[0] = beg;
	key->width = 1;
	while (check_width(str[beg]) == 1)
		beg++;
	key->width_pos[1] = beg;
	key->index = beg;
	return (key);
}

t_arg			*prec_key(t_arg *key, char *str, int beg)
{
	beg++;
	key->prec_pos[0] = beg;
	key->prec = 1;
	while (check_width(str[beg]) == 1)
		beg++;
	key->prec_pos[1] = beg;
	key->index = beg;
	return (key);
}

t_arg			*length_key(t_arg *key, char *str, int beg)
{
	key->length_pos[0] = beg;
	key->length = 1;
	while (check_length(str[beg]) == 1)
		beg++;
	key->length_pos[1] = beg - 1;
	key->index = beg;
	return (key);
}

t_arg			*specs_key(t_arg *key, char *str, int beg)
{
	key->specs_pos[0] = beg;
	key->specs = 1;
	while (check_specs(str[beg]) == 1)
		beg++;
	key->specs_pos[1] = beg - 1;
	key->index = beg;
	return (key);
}
