/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 12:58:24 by amagnan           #+#    #+#             */
/*   Updated: 2019/12/17 20:13:07 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double		get_a(t_ray *ray, t_object *obj)
{
	t_vec	tmp;
	double	dot;

	dot = vec_dot_product(ray->ray_d, obj->cylinder->direction);
	tmp.x = dot * obj->cylinder->direction.x;
	tmp.y = dot * obj->cylinder->direction.y;
	tmp.z = dot * obj->cylinder->direction.z;
	tmp = vec_sub(ray->ray_d, tmp);
	return (vec_dot_product(tmp, tmp));
}

static double		get_b(t_ray *ray, t_object *obj, t_vec diff)
{
	t_vec	tmp;
	t_vec	tmp2;
	double	dot;

	dot = vec_dot_product(diff, obj->cylinder->direction);
	tmp.x = dot * obj->cylinder->direction.x;
	tmp.y = dot * obj->cylinder->direction.y;
	tmp.z = dot * obj->cylinder->direction.z;
	tmp = vec_sub(diff, tmp);
	dot = vec_dot_product(ray->ray_d, obj->cylinder->direction);
	tmp2.x = dot * obj->cylinder->direction.x;
	tmp2.y = dot * obj->cylinder->direction.y;
	tmp2.z = dot * obj->cylinder->direction.z;
	tmp2 = vec_sub(ray->ray_d, tmp2);
	return (2 * vec_dot_product(tmp2, tmp));
}

static double		get_c(t_object *obj, t_vec diff)
{
	t_vec	tmp;
	double	dot;

	dot = vec_dot_product(diff, obj->cylinder->direction);
	tmp.x = dot * obj->cylinder->direction.x;
	tmp.y = dot * obj->cylinder->direction.y;
	tmp.z = dot * obj->cylinder->direction.z;
	tmp = vec_sub(diff, tmp);
	return (vec_dot_product(tmp, tmp) - obj->cylinder->radius *
	obj->cylinder->radius);
}

static void			find_quadratic_equa_coefs_cylinder(t_ray *ray,
					t_object *obj, double *coefs)
{
	t_vec	diff;

	diff = vec_sub(ray->ray_o, obj->cylinder->base);
	coefs[0] = get_a(ray, obj);
	coefs[1] = get_b(ray, obj, diff);
	coefs[2] = get_c(obj, diff);
}

bool				find_intersection_cylinder(t_ray *ray, t_object *obj,
					double *object_dist)
{
	double	coefs[3];
	double	sols[2];

	*object_dist = INFINITY;
	find_quadratic_equa_coefs_cylinder(ray, obj, coefs);
	if (TRUE == solve_quadratic_equa(coefs[0], coefs[1], coefs[2], sols))
		object_dist = get_intersection_cylinder(ray, obj, object_dist, sols);
	if (*object_dist != INFINITY)
		return (TRUE);
	return (FALSE);
}
