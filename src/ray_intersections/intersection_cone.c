/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 14:29:56 by anjansse          #+#    #+#             */
/*   Updated: 2019/12/17 19:51:22 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		find_quadratic_equa_coefs_cone(t_ray *ray,
				t_object *obj, double *coefs)
{
	double		cos_squ;
	double		dot_dv;
	t_vec		vec_co;

	cos_squ = pow(cos(obj->cone->half_angle), 2.0);
	dot_dv = vec_dot_product(ray->ray_d, obj->cone->axis_vector);
	vec_co = vec_sub(ray->ray_o, obj->cone->cone_tips);
	coefs[0] = pow(dot_dv, 2.0) - cos_squ;
	coefs[1] = 2 * ((dot_dv * vec_dot_product(vec_co, obj->cone->axis_vector)
	- vec_dot_product(ray->ray_d, vec_co) * cos_squ));
	coefs[2] = pow(vec_dot_product(vec_co, obj->cone->axis_vector), 2.0)
	- vec_dot_product(vec_co, vec_co) * cos_squ;
}

bool			find_intersection_cone(t_ray *ray,
				t_object *obj, double *object_dist)
{
	double		coefs[3];
	double		sols[2];

	*object_dist = INFINITY;
	find_quadratic_equa_coefs_cone(ray, obj, coefs);
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
