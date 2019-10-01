/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_roty.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 12:13:27 by anjansse          #+#    #+#             */
/*   Updated: 2019/09/11 12:13:37 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

void			vec_roty(t_vec *vec, double angle)
{
	vec->x = ((vec->x * cos(angle)) + (vec->z * sin(angle)));
	vec->z = ((-vec->x * sin(angle)) + (vec->z * cos(angle)));
}
