/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 13:35:03 by amagnan           #+#    #+#             */
/*   Updated: 2019/12/22 09:18:28 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#define LUM		ft_luminosity

/*
** ----------------------------------------------------------------------------
**	Looping through all the lights and looking for intersections
**	Getting the new ray direction and origin
**	If intersection then it's in shadow so we don't do anything,
**	else add color contribution
**	Getting the facing ratio (exposure to light source)
**	Adding the color contributions. I cap the color value to the
**	intersected object's original color for now.
** ----------------------------------------------------------------------------
*/

t_color			define_and_cast_shadow_rays(t_rt *rt, t_ray *ray,\
				t_object *closest_object, double closest_object_distance)
{
	t_ray		shadow_ray;
	t_vec		hitpoint;
	t_vec		normal;
	t_light		*current_light;
	t_color		color;

	if (!check_material(closest_object, DIFFUSE) &&
	!check_material(closest_object, SCALAR))
		return ((t_color){0x000000, 0});
	hitpoint = vec_add(ray->ray_o, vec_scale(ray->ray_d,
	closest_object_distance));
	normal = get_normal_at_hitpoint(ray, closest_object, hitpoint);
	current_light = rt->light;
	shadow_ray.inside_flag = 0;
	color.color = 0x000000;
	color.intensity = 0;
	while (current_light)
	{
		shadow_ray.ray_d = vec_normalize(vec_sub(current_light->pos, hitpoint));
		shadow_ray.ray_o = hitpoint;
		if (check_obstructing_object_before_light(
			rt, shadow_ray, current_light, hitpoint))
			color = get_color_object(color, current_light,
			closest_object, normal, shadow_ray);
		current_light = current_light->next;
	}
	return (color);
}

/*
** ----------------------------------------------------------------------------
** Function being called by `rt_game_loop` to update everything
** to the frame buffer. (objects, background, ..)
**
** @param {t_rt *} rt - Main structure for RT.
** ----------------------------------------------------------------------------
*/

t_color			define_and_cast_reflected_ray(t_rt *rt, t_ray *ray,\
				t_object *closest_object, double closest_object_distance)
{
	t_ray		ref_ray;
	t_vec		hitpoint;
	t_vec		normal;

	hitpoint = vec_add(ray->ray_o, vec_scale(ray->ray_d,
	closest_object_distance));
	normal = get_normal_at_hitpoint(ray, closest_object, hitpoint);
	ref_ray.depth = ++ray->depth;
	ref_ray.pix_nb = ray->pix_nb;
	ref_ray.ray_o = hitpoint;
	ref_ray.ray_d = vec_sub(ray->ray_d, vec_scale(normal, 2 *\
						vec_dot_product(ray->ray_d, normal)));
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
				return ((t_color){LUM((rt_cast_ray(rt, ray).color), 0.8), 1});
		}
		else if (closest_object->type == NB_PLANE)
		{
			if (closest_object->plane->material == REFRACTION)
				return ((t_color){LUM((rt_cast_ray(rt, ray).color), 0.8), 1});
		}
		else if (closest_object->type == NB_CYLINDER)
		{
			if (closest_object->cylinder->material == REFRACTION)
				return ((t_color){LUM((rt_cast_ray(rt, ray).color), 0.8), 1});
		}
		else if (closest_object->type == NB_CONE)
		{
			if (closest_object->cone->material == REFRACTION)
				return ((t_color){LUM((rt_cast_ray(rt, ray).color), 0.8), 1});
		}
	}
	return ((t_color){0x000000, 0});
}

/*
** ----------------------------------------------------------------------------
** Function being called by `rt_game_loop` to update everything
** to the frame buffer. (objects, background, ..)
**
** @param {t_rt *} rt - Main structure for RT.
** ----------------------------------------------------------------------------
*/

t_color			define_and_cast_refracted_ray(t_rt *rt, t_ray *ray,\
				t_object *closest_object, double clos_obj_dist)
{
	t_ray		refraction_ray;

	get_refracted_ray_infos(ray, &refraction_ray,
	closest_object, clos_obj_dist);
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
	if ((TRUE == find_closest_intersected_object(rt, ray,
	&closest_object, &closest_object_distance)))
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
		return ((t_color){rt->win.d_background[ray->pix_nb], 1});
}
