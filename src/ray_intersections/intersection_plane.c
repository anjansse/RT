/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 14:30:26 by anjansse          #+#    #+#             */
/*   Updated: 2019/12/17 20:14:13 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** ----------------------------------------------------------------------------
**	If the denominator is (close to) zero, then it means that the ray is \
**	parallel to the plane and thus, we consider there is no intersection \
**	in this case.
**	See implementation details here:
**	https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-\
**	tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
**
**	@param {p0} is the point on the plane the closest to the origin (0, 0, 0)
** ----------------------------------------------------------------------------
*/

bool			find_intersection_plane(t_ray *ray, t_object *obj,
										double *object_dist)
{
	double	denominator;
	double	numerator;
	double	intersection_dist;
	t_vec	p0;

	*object_dist = INFINITY;
	denominator = vec_dot_product(ray->ray_d, obj->plane->normal);
	if (denominator > EPSILON || denominator < -EPSILON)
	{
		vec_set(&p0, obj->plane->normal.x * obj->plane->dist_to_origin, \
						obj->plane->normal.y * obj->plane->dist_to_origin, \
						obj->plane->normal.z * obj->plane->dist_to_origin);
		numerator = vec_dot_product(vec_sub(p0, ray->ray_o),
		obj->plane->normal);
		intersection_dist = numerator / denominator;
		if (intersection_dist > EPSILON && intersection_dist < *object_dist)
			*object_dist = intersection_dist;
	}
	if (*object_dist != INFINITY)
		return (TRUE);
	return (FALSE);
}
