/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_functions_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:55:12 by anjansse          #+#    #+#             */
/*   Updated: 2019/12/22 09:17:47 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			get_object_color(t_color *color, t_object *closest_object)
{
	if (closest_object->type == NB_SPHERE)
		color->color = closest_object->sphere->color;
	else if (closest_object->type == NB_PLANE)
		color->color = closest_object->plane->color;
	else if (closest_object->type == NB_CYLINDER)
		color->color = closest_object->cylinder->color;
	else if (closest_object->type == NB_CONE)
		color->color = closest_object->cone->color;
}

t_color				get_color_object(t_color color, t_light *current_light,
					t_object *closest_object, t_vec normal, t_ray shadow_ray)
{
	double		facing_ratio;

	if (shadow_ray.inside_flag && closest_object->type == NB_CYLINDER)
		normal = vec_scale(normal, -1);
	if ((facing_ratio = vec_dot_product(normal, shadow_ray.ray_d)) < 0)
		facing_ratio = 0;
	color.intensity += current_light->intensity * facing_ratio;
	get_object_color(&color, closest_object);
	if (closest_object->type != NB_PLANE &&
	facing_ratio >= 0.98500 && facing_ratio <= 1 &&
	check_material(closest_object, SCALAR))
	{
		color.color = calculate_scalar(ft_luminosity(color.color,
		color.intensity), facing_ratio);
		color.intensity = 1;
	}
	return (color);
}

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
	refraction_ray->ray_o = vec_add(ray->ray_o, vec_scale(ray->ray_d,
	clos_obj_dist));
	vec_i = ray->ray_d;
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

	*hitpoint = vec_add(ray->ray_o, vec_scale(ray->ray_d, *object_dist));
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
