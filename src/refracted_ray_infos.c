/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refracted_ray_infos.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:55:12 by anjansse          #+#    #+#             */
/*   Updated: 2019/12/17 15:47:23 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void				get_refracted_ray_infos(t_ray *ray, t_ray *refraction_ray,\
		t_object *closest_object, double clos_obj_dist)
{
	double		c1;
	double		c2;
	double		ndelta;
	t_vec		vec_i;
	t_vec		vec_n;

	refraction_ray->pix_nb = ray->pix_nb;
	refraction_ray->depth = ++ray->depth;
	refraction_ray->ray_o = vec_add(RAY_O, vec_scale(RAY_D, clos_obj_dist));
	vec_i = RAY_D;
	vec_n = get_normal_at_hitpoint(ray, closest_object, refraction_ray->ray_o);
	ndelta = 1 / 1.3;
	c1 = vec_dot_product(vec_n, vec_i);
	c2 = sqrt(1 - (ndelta * ndelta) * (1 - (c1 * c1)));
	refraction_ray->ray_d = vec_sub(vec_scale((vec_add(vec_i,\
	vec_scale(vec_n, c1))), ndelta), vec_scale(vec_n, c2));
}

static double		get_hitpoint_scale(t_ray *ray, t_vec *hitpoint,
					t_object *obj, double *object_dist)
{
	double		scale;

	*hitpoint = vec_add(RAY_O, vec_scale(RAY_D, *object_dist));
	scale = (vec_dot_product(*hitpoint, obj->cylinder->direction)
	- vec_dot_product(obj->cylinder->base, obj->cylinder->direction))
	/ vec_dot_product(obj->cylinder->direction, obj->cylinder->direction);
	return (scale);
}

double				*get_intersection_cylinder(t_ray *ray, t_object *obj,
					double *object_dist, double *sols)
{
	double	scale;
	t_vec	hitpoint;

	if (sols[0] > EPSILON && sols[0] < *object_dist)
		*object_dist = sols[0];
	if (sols[1] > EPSILON && sols[1] < *object_dist)
		*object_dist = sols[1];
	scale = get_hitpoint_scale(ray, &hitpoint, obj, object_dist);
	if (scale > obj->cylinder->height || scale < 0)
	{
		*object_dist = (*object_dist == sols[0]) ? sols[1] : sols[0];
		ray->inside_flag = TRUE;
		scale = get_hitpoint_scale(ray, &hitpoint, obj, object_dist);
		if (scale > obj->cylinder->height || scale < 0)
		{
			*object_dist = INFINITY;
			ray->inside_flag = FALSE;
		}
	}
	return (object_dist);
}
