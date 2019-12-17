/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <amagnan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 13:35:03 by amagnan           #+#    #+#             */
/*   Updated: 2019/12/17 13:16:52 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

#define INTERSECTION_OBJ (TRUE == find_closest_intersected_object(rt, ray, &closest_object, &closest_object_distance))

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

	if (vec_dot_product(RAY_D, closest_object->plane->normal) > 0)
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

static int		check_material(t_object *closest_object, int material)
{
	if (closest_object->type == NB_CONE)
	{
		if (closest_object->cone->material == material)
			return (1);
	}
	else if (closest_object->type == NB_CYLINDER)
	{
		if (closest_object->cylinder->material == material)
			return (1);
	}
	else if (closest_object->type == NB_PLANE)
	{
		if (closest_object->plane->material == material)
			return (1);
	}
	else if (closest_object->type == NB_SPHERE)
	{
		if (closest_object->sphere->material == material)
			return (1);
	}
	return (0);
}

/*
**	Looping through all the lights and looking for intersections
**	Getting the new ray direction and origin
**	If intersection then it's in shadow so we don't do anything,
**	else add color contribution
**	Getting the facing ratio (exposure to light source)
**	Adding the color contributions. I cap the color value to the
**	intersected object's original color for now.
*/

t_color			define_and_cast_shadow_rays(t_rt *rt, t_ray *ray,\
												t_object *closest_object,
												double closest_object_distance)
{
	t_ray		shadow_ray;
	t_vec		hitpoint;
	t_vec		normal;
	t_light		*current_light;
	double		facing_ratio;
	t_color		color;
	t_object	*new_closest_object;
	double		new_distance;

	if (!check_material(closest_object, DIFFUSE) && !check_material(closest_object, SCALAR))
		return ((t_color){0x000000, 0});
	hitpoint = vec_add(RAY_O, vec_scale(RAY_D, closest_object_distance));
	normal = get_normal_at_hitpoint(ray, closest_object, hitpoint);
	current_light = rt->light;
	color.color = 0x000000;
	color.intensity = 0;
	shadow_ray.inside_flag = 0;
	while (current_light)
	{
		new_closest_object = NULL;
		new_distance = INFINITY;
		shadow_ray.ray_d = vec_normalize(vec_sub(current_light->pos, hitpoint));
		shadow_ray.ray_o = hitpoint;
		if (!find_closest_intersected_object(rt, &shadow_ray,\
		&new_closest_object, &new_distance) ||
		(find_closest_intersected_object(rt, &shadow_ray, &new_closest_object,\
		&new_distance) && (new_distance > vec_magnitude(vec_sub(\
		current_light->pos, hitpoint)))))
		{
			if (shadow_ray.inside_flag && closest_object->type == NB_CYLINDER)
				normal = vec_scale(normal, -1);
			if ((facing_ratio = vec_dot_product(normal, shadow_ray.ray_d)) < 0)
				facing_ratio = 0;
			color.intensity += current_light->intensity * facing_ratio;
			if (closest_object->type == NB_SPHERE)
				color.color = closest_object->sphere->color;
			else if (closest_object->type == NB_PLANE)
				color.color = closest_object->plane->color;
			else if (closest_object->type == NB_CYLINDER)
				color.color = closest_object->cylinder->color;
			else if (closest_object->type == NB_CONE)
				color.color = closest_object->cone->color;
			if (closest_object->type != NB_PLANE &&
			facing_ratio >= 0.98500 && facing_ratio <= 1 && check_material(closest_object, SCALAR))
			{
				color.color = calculate_scalar(ft_luminosity(color.color, color.intensity), facing_ratio);
				color.intensity = 1;
			}
		}
		current_light = current_light->next;
	}
	return (color);
}

static t_color	get_reflected_ray_color(t_rt *rt, t_ray *reflection_ray,\
				t_object *object)
{
	t_color		color;

	if (object->type == NB_SPHERE && object->sphere->material == REFLECTION)
	{
		color = rt_cast_ray(rt, reflection_ray);
		return ((t_color){color.color, color.intensity * 0.8});
	}
	else if (object->type == NB_PLANE && object->plane->material == REFLECTION)
	{
		color = rt_cast_ray(rt, reflection_ray);
		return ((t_color){color.color, color.intensity * 0.8});
	}
	else if (object->type == NB_CYLINDER &&
	object->cylinder->material == REFLECTION)
	{
		color = rt_cast_ray(rt, reflection_ray);
		return ((t_color){color.color, color.intensity * 0.8});
	}
	else if (object->type == NB_CONE && object->cone->material == REFLECTION)
	{
		color = rt_cast_ray(rt, reflection_ray);
		return ((t_color){color.color, color.intensity * 0.8});
	}
	return ((t_color){0x000000, 0});
}

t_color			define_and_cast_reflected_ray(t_rt *rt, t_ray *ray,\
												t_object *closest_object,
												double closest_object_distance)
{
	t_ray		ref_ray;
	t_vec		hitpoint;
	t_vec		normal;

	hitpoint = vec_add(RAY_O, vec_scale(RAY_D, closest_object_distance));
	normal = get_normal_at_hitpoint(ray, closest_object, hitpoint);
	ref_ray.depth = ++ray->depth;
	ref_ray.pix_nb = ray->pix_nb;
	ref_ray.ray_o = hitpoint;
	ref_ray.ray_d = vec_sub(RAY_D, vec_scale(normal, 2 *\
						vec_dot_product(RAY_D, normal)));
	if (ref_ray.depth < MAX_DEPTH)
		return (get_reflected_ray_color(rt, &ref_ray, closest_object));
	return ((t_color){0x000000, 0});
}

static t_color	get_color(t_rt *rt, t_ray *ray, t_object *closest_object)
{
	if (ray->depth < MAX_DEPTH)
	{
		if (closest_object->type == NB_SPHERE)
		{
			if (closest_object->sphere->material == REFRACTION)
				return ((t_color){ft_luminosity((rt_cast_ray(rt, ray).color), 0.8), 1});
		}
		else if (closest_object->type == NB_PLANE)
		{
			if (closest_object->plane->material == REFRACTION)
				return ((t_color){ft_luminosity((rt_cast_ray(rt, ray).color), 0.8), 1});
		}
		else if (closest_object->type == NB_CYLINDER)
		{
			if (closest_object->cylinder->material == REFRACTION)
				return ((t_color){ft_luminosity((rt_cast_ray(rt, ray).color), 0.8), 1});
		}
		else if (closest_object->type == NB_CONE)
		{
			if (closest_object->cone->material == REFRACTION)
				return ((t_color){ft_luminosity((rt_cast_ray(rt, ray).color), 0.8), 1});
		}
	}
	return ((t_color){0x000000, 0});
}

static void		get_values(t_ray *ray, t_ray *refraction_ray,\
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

t_color			define_and_cast_refracted_ray(t_rt *rt, t_ray *ray,\
t_object *closest_object, double clos_obj_dist)
{
	t_ray		refraction_ray;

	get_values(ray, &refraction_ray, closest_object, clos_obj_dist);
	return (get_color(rt, &refraction_ray, closest_object));
}

/*
** ----------------------------------------------------------------------------
** Recursive function which casts a ray through the scene. Type of ray will
** influence what informations it will receive (ray_origin / ray_direction),
** and when a ray has hit it's target or is being casted too many times,
** calls a shading function to color the pixel of which the ray is associated
** with.
**
** @param {t_rt *} rt - Main structure for RT.
** @param {t_ray *} ray - Ray that has to be casted from a point to another.
** ----------------------------------------------------------------------------
*/

t_color			rt_cast_ray(t_rt *rt, t_ray *ray)
{
	double		closest_object_distance;
	t_object	*closest_object;
	t_color		refl;
	t_color		refr;
	t_color		scat;

	closest_object_distance = INFINITY;
	closest_object = NULL;
	if (INTERSECTION_OBJ)
	{
		refl = define_and_cast_reflected_ray(rt, ray,\
					closest_object, closest_object_distance);
		refr = define_and_cast_refracted_ray(rt, ray,\
					closest_object, closest_object_distance);
		scat = define_and_cast_shadow_rays(rt, ray,\
					closest_object, closest_object_distance);
		return (combine_colors(refl, refr,
								scat));
	}
	else
		return ((t_color){DEFAULT_BACKGROUND[ray->pix_nb], 1});
}
