#include "RT.h"

# define AX_VEC		obj->cone->axis_vector
# define HALF_ANGLE	obj->cone->half_angle
# define CONE_TIPS	obj->cone->cone_tips
# define COS2		pow(cos(HALF_ANGLE), 2.0)
# define dot_DV		vec_dot_product(RAY_D, AX_VEC)
# define CO			vec_sub(RAY_O, CONE_TIPS)

# define MIN_Y		obj->cone->axis_vector.y
# define MAX_Y		obj->cone->cone_tips.y

static void		find_quadratic_equa_coefs_cone(t_ray *ray, t_object *obj, double *coefs)
{
	coefs[0] = pow(dot_DV, 2.0) - COS2;
	coefs[1] = 2 * ((vec_dot_product(RAY_D, AX_VEC) * vec_dot_product(CO, AX_VEC) - vec_dot_product(RAY_D, CO) * COS2));
	coefs[2] = pow(vec_dot_product(CO, AX_VEC), 2.0) - vec_dot_product(CO, CO) * COS2;
}

bool			find_intersection_cone(t_ray *ray, t_object *obj, double *object_dist)
{
	double		coefs[3];
	double		sols[2];
	double		y[2];
	double		max_y;
	double		min_y;

	*object_dist = INFINITY;
	find_quadratic_equa_coefs_cone(ray, obj, coefs);
	if (TRUE == solve_quadratic_equa(coefs[0], coefs[1], coefs[2], sols))
	{
		y[0] = RAY_O.y + RAY_D.y * sols[0];
        y[1] = RAY_O.y + RAY_D.y * sols[1];
		max_y = (CONE_TIPS.y >= AX_VEC.y) ? CONE_TIPS.y : AX_VEC.y;
		min_y = (CONE_TIPS.y >= AX_VEC.y) ? AX_VEC.y : CONE_TIPS.y;

		if (y[0] <= max_y && y[0] >= min_y && sols[0] > EPSILON && sols[0] < *object_dist)
			*object_dist = sols[0];
		if (y[1] <= max_y && y[1] >= min_y && sols[1] > EPSILON && sols[1] < *object_dist)
			*object_dist = sols[1];
	}
	if (*object_dist != INFINITY)
		return (TRUE);
	return (FALSE);
}

// static double	quadratic_operation_find_a(t_ray *ray, t_object *obj)
// {
// 	double dot_prod;
// 	double cos_rad;

// 	dot_prod = vec_dot_product(RAY_D, obj->cone->axis_vector);
// 	cos_rad = cos(obj->cone->half_angle);
// 	return (dot_prod * dot_prod - cos_rad * cos_rad);
// }

// static double	quadratic_operation_find_b(t_ray *ray, t_object *obj, t_vec diff)
// {
// 	double cos_rad;
// 	double dot_prod1;
// 	double dot_prod2;
// 	double dot_prod3;

// 	dot_prod1 = vec_dot_product(RAY_D, obj->cone->axis_vector);
// 	dot_prod2 = vec_dot_product(diff, obj->cone->axis_vector);
// 	dot_prod3 = vec_dot_product(RAY_D, diff);
// 	cos_rad = cos(obj->cone->half_angle);
// 	cos_rad *= cos_rad;
// 	return (2 * (dot_prod1 * dot_prod2 - dot_prod3 * cos_rad));
// }

// static double	quadratic_operation_find_c(t_object *obj, t_vec diff)
// {
// 	double cos_rad;
// 	double dot_prod1;
// 	double dot_prod2;

// 	dot_prod1 = vec_dot_product(diff, obj->cone->axis_vector);
// 	dot_prod2 = vec_dot_product(diff, diff);
// 	cos_rad = cos(obj->cone->half_angle);
// 	cos_rad *= cos_rad;
// 	return (dot_prod1 * dot_prod1 - dot_prod2 * cos_rad);
// }

// bool			find_intersection_cone(t_ray *ray, t_object *obj, double *object_dist)
// {
// 	double		coefs[3];
// 	double		sols[2];

// 	*object_dist = INFINITY;
// 	coefs[0] = quadratic_operation_find_a(ray, obj);
// 	coefs[1] = quadratic_operation_find_b(ray, obj, vec_sub(RAY_O, obj->cone->cone_tips));
// 	coefs[2] = quadratic_operation_find_c(obj, vec_sub(RAY_O, obj->cone->cone_tips));
// 	if (TRUE == solve_quadratic_equa(coefs[0], coefs[1], coefs[2], sols))
// 	{
// 		if (sols[0] > EPSILON && sols[0] < *object_dist)
// 			*object_dist = sols[0];
// 		if (sols[1] > EPSILON && sols[1] < *object_dist)
// 			*object_dist = sols[1];
// 	}
// 	if (*object_dist != INFINITY)
// 		return (TRUE);
// 	return (FALSE);
// }