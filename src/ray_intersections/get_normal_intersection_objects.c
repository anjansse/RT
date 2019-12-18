/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal_intersection_objects.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:32:13 by anjansse          #+#    #+#             */
/*   Updated: 2019/12/17 19:50:23 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec			get_normal_intersection_sphere(t_object *closest_object,
												t_vec hitpoint)
{
	t_vec		normal;

	normal = vec_normalize(vec_sub(hitpoint, closest_object->sphere->center));
	return (normal);
}

t_vec			get_normal_intersection_plane(t_ray *ray,
												t_object *closest_object)
{
	t_vec		normal;

	if (vec_dot_product(ray->ray_d, closest_object->plane->normal) > 0)
		normal = vec_scale(closest_object->plane->normal, -1);
	else
		normal = closest_object->plane->normal;
	return (normal);
}

t_vec			get_normal_intersection_cylinder(t_object *closest_object,\
												t_vec hitpoint)
{
	t_vec		normal;
	t_vec		new_vec;
	double		scale;

	scale = vec_dot_product(hitpoint, closest_object->cylinder->direction);
	scale -= vec_dot_product(closest_object->cylinder->base,
								closest_object->cylinder->direction);
	scale /= vec_dot_product(closest_object->cylinder->direction,
								closest_object->cylinder->direction);
	new_vec = vec_scale(closest_object->cylinder->direction, scale);
	new_vec = vec_add(new_vec, closest_object->cylinder->base);
	normal = vec_normalize(vec_sub(hitpoint, new_vec));
	return (normal);
}

t_vec			get_normal_intersection_cone(t_object *closest_object,\
											t_vec hitpoint)
{
	t_vec	normal;
	t_vec	new_vec;
	t_vec	cone_tip;
	t_vec	axis_vector;
	double	scale;

	cone_tip = closest_object->cone->cone_tips;
	axis_vector = closest_object->cone->axis_vector;
	scale = 2 * vec_dot_product(cone_tip, hitpoint);
	scale -= vec_dot_product(cone_tip, cone_tip);
	scale -= vec_dot_product(hitpoint, hitpoint);
	scale /= vec_dot_product(vec_sub(cone_tip, hitpoint), axis_vector);
	new_vec = vec_scale(axis_vector, scale);
	new_vec = vec_add(new_vec, cone_tip);
	normal = vec_normalize(vec_sub(hitpoint, new_vec));
	return (normal);
}

t_vec			get_normal_at_hitpoint(t_ray *ray, t_object *closest_object,
										t_vec hitpoint)
{
	t_vec		normal;

	normal = vec_new(0, 0, 0);
	if (closest_object->type == NB_SPHERE)
		normal = get_normal_intersection_sphere(closest_object, hitpoint);
	else if (closest_object->type == NB_PLANE)
		normal = get_normal_intersection_plane(ray, closest_object);
	else if (closest_object->type == NB_CYLINDER)
		normal = get_normal_intersection_cylinder(closest_object, hitpoint);
	else if (closest_object->type == NB_CONE)
		normal = get_normal_intersection_cone(closest_object, hitpoint);
	return (normal);
}
