/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_rotxyz.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 12:13:19 by anjansse          #+#    #+#             */
/*   Updated: 2019/09/11 12:13:20 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

void			vec_rotxyz(t_vec *vec, double angle)
{
	vec_rotx(vec, angle);
	vec_roty(vec, angle);
	vec_rotz(vec, angle);
}
