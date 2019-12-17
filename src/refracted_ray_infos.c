/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refracted_ray_infos.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:55:12 by anjansse          #+#    #+#             */
/*   Updated: 2019/12/17 14:13:34 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void		get_refracted_ray_infos(t_ray *ray, t_ray *refraction_ray,\
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
