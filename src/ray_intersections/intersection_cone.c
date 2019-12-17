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
