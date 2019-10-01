/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_rotz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 12:13:42 by anjansse          #+#    #+#             */
/*   Updated: 2019/09/11 12:13:50 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

void			vec_rotz(t_vec *vec, double angle)
{
	vec->x = ((vec->x * cos(angle)) - (vec->y * sin(angle)));
	vec->y = ((vec->x * sin(angle)) + (vec->y * cos(angle)));
}
