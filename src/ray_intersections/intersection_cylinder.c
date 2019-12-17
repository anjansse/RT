/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 12:58:24 by amagnan           #+#    #+#             */
/*   Updated: 2019/12/17 15:11:22 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static double		get_a(t_ray *ray, t_object *obj)
{
	t_vec	tmp;
	double	dot;

	dot = vec_dot_product(RAY_D, CYLINDER->direction);
	tmp.x = dot * CYLINDER->direction.x;
	tmp.y = dot * CYLINDER->direction.y;
	tmp.z = dot * CYLINDER->direction.z;
	tmp = vec_sub(RAY_D, tmp);
	return (vec_dot_product(tmp, tmp));
}

static double		get_b(t_ray *ray, t_object *obj, t_vec diff)
{
	t_vec	tmp;
	t_vec	tmp2;
	double	dot;

	dot = vec_dot_product(diff, CYLINDER->direction);
	tmp.x = dot * CYLINDER->direction.x;
	tmp.y = dot * CYLINDER->direction.y;
	tmp.z = dot * CYLINDER->direction.z;
	tmp = vec_sub(diff, tmp);
	dot = vec_dot_product(RAY_D, CYLINDER->direction);
	tmp2.x = dot * CYLINDER->direction.x;
	tmp2.y = dot * CYLINDER->direction.y;
	tmp2.z = dot * CYLINDER->direction.z;
	tmp2 = vec_sub(RAY_D, tmp2);
	return (2 * vec_dot_product(tmp2, tmp));
}

static double		get_c(t_object *obj, t_vec diff)
{
	t_vec	tmp;
	double	dot;

	dot = vec_dot_product(diff, CYLINDER->direction);
	tmp.x = dot * CYLINDER->direction.x;
	tmp.y = dot * CYLINDER->direction.y;
	tmp.z = dot * CYLINDER->direction.z;
	tmp = vec_sub(diff, tmp);
	return (vec_dot_product(tmp, tmp) - CYLINDER->radius * CYLINDER->radius);
}

static void			find_quadratic_equa_coefs_cylinder(t_ray *ray,
					t_object *obj, double *coefs)
{
	t_vec	diff;

	diff = vec_sub(RAY_O, CYLINDER->base);
	coefs[0] = get_a(ray, obj);
	coefs[1] = get_b(ray, obj, diff);
	coefs[2] = get_c(obj, diff);
}

static double		get_hitpoint_scale(t_ray *ray, t_vec *hitpoint, t_object *obj, double *object_dist)
{
		double		scale;
		
		*hitpoint = vec_add(RAY_O, vec_scale(RAY_D, *object_dist));
		scale = (vec_dot_product(*hitpoint, obj->cylinder->direction)
		- vec_dot_product(obj->cylinder->base, obj->cylinder->direction))
		/ vec_dot_product(obj->cylinder->direction, obj->cylinder->direction);
		return (scale);
}

bool				find_intersection_cylinder(t_ray *ray, t_object *obj,
					double *object_dist)
{
	double	coefs[3];
	double	sols[2];
	t_vec	hitpoint;
	double	scale;

	*object_dist = INFINITY;
	find_quadratic_equa_coefs_cylinder(ray, obj, coefs);
	if (TRUE == solve_quadratic_equa(coefs[0], coefs[1], coefs[2], sols))
	{
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
	}
	if (*object_dist != INFINITY)
		return (TRUE);
	return (FALSE);
}
