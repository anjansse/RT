/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 14:30:33 by anjansse          #+#    #+#             */
/*   Updated: 2019/12/17 20:12:35 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** ----------------------------------------------------------------------------
** The functions below allow to determine the coefs of the quadratic equation
** to solve in order to find the intersection points between the object and
** the ray at hand.
** ----------------------------------------------------------------------------
*/

void			find_quadratic_equa_coefs_sphere(t_ray *ray, t_object *obj,
												double *coefs)
{
	coefs[0] = vec_dot_product(ray->ray_d, ray->ray_d);
	coefs[1] = 2 * vec_dot_product(ray->ray_d,
	vec_sub(ray->ray_o, obj->sphere->center));
	coefs[2] = vec_dot_product(vec_sub(ray->ray_o, obj->sphere->center),
	vec_sub(ray->ray_o, obj->sphere->center)) -
	obj->sphere->radius * obj->sphere->radius;
}

bool			find_intersection_sphere(t_ray *ray, t_object *obj,
										double *object_dist)
{
	double		coefs[3];
	double		sols[2];

	*object_dist = INFINITY;
	find_quadratic_equa_coefs_sphere(ray, obj, coefs);
	if (TRUE == solve_quadratic_equa(coefs[0], coefs[1], coefs[2], sols))
	{
		if (sols[0] > EPSILON && sols[0] < *object_dist)
			*object_dist = sols[0];
		if (sols[1] > EPSILON && sols[1] < *object_dist)
			*object_dist = sols[1];
	}
	if (*object_dist != INFINITY)
		return (TRUE);
	return (FALSE);
}
