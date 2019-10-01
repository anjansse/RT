/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_rotx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 12:12:49 by anjansse          #+#    #+#             */
/*   Updated: 2019/09/11 12:12:59 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

void			vec_rotx(t_vec *vec, double angle)
{
	vec->y = ((vec->y * cos(angle)) + (vec->z * sin(angle)));
	vec->z = ((-vec->y * sin(angle)) + (vec->z * cos(angle)));
}
