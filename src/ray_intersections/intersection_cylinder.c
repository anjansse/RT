#include "RT.h"

# define                MIN_Y CYLINDER->base.y
# define                MAX_Y (CYLINDER->base.y + CYLINDER->height)

static double           get_a(t_ray *ray, t_object *obj) {
    t_vec               tmp;
    double              dot;

    dot = vec_dot_product(RAY_D, CYLINDER->direction);
	tmp.x = dot * CYLINDER->direction.x;
	tmp.y = dot * CYLINDER->direction.y;
	tmp.z = dot * CYLINDER->direction.z;
	tmp = vec_sub(RAY_D, tmp);
    return (vec_dot_product(tmp, tmp));
}

static double           get_b(t_ray *ray, t_object *obj, t_vec diff) {

    t_vec               tmp;
    t_vec               tmp2;
    double              dot;

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

static double           get_c(t_object *obj, t_vec diff)
{
    t_vec               tmp;
    double              dot;

    dot = vec_dot_product(diff, CYLINDER->direction);
	tmp.x = dot * CYLINDER->direction.x;
	tmp.y = dot * CYLINDER->direction.y;
	tmp.z = dot * CYLINDER->direction.z;
	tmp = vec_sub(diff, tmp);

	return (vec_dot_product(tmp, tmp) - CYLINDER->radius * CYLINDER->radius);
}

static void             find_quadratic_equa_coefs_cylinder(t_ray *ray, t_object *obj, double *coefs)
{
    t_vec               diff;

/*
    Might need a bit of change in this line because I get the
    diff between origin and BASE of the cylinder
*/
    diff = vec_sub(RAY_O, CYLINDER->base);

	coefs[0] = get_a(ray, obj);
	coefs[1] = get_b(ray, obj, diff);
	coefs[2] = get_c(obj, diff);
}

bool			find_intersection_cylinder(t_ray *ray, t_object *obj, double *object_dist)
{
    double      coefs[3];
    double      sols[2];
    double      y[2];

    *object_dist = INFINITY;
    find_quadratic_equa_coefs_cylinder(ray, obj, coefs);
    if (TRUE == solve_quadratic_equa(coefs[0], coefs[1], coefs[2], sols))
    {
        y[0] = RAY_O.y + RAY_D.y * sols[0];
        y[1] = RAY_O.y + RAY_D.y * sols[1];

        if (y[0] > MIN_Y && y[0] < MAX_Y && sols[0] > EPSILON && sols[0] < *object_dist)
			*object_dist = sols[0];
		if (y[1] > MIN_Y && y[1] < MAX_Y && sols[1] > EPSILON && sols[1] < *object_dist)
			*object_dist = sols[1];
        // Need to find a way to get the caps at the top and bottom
        // ->   it's written on your website https://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html#eqn:rectray
    }       
    if (*object_dist != INFINITY)
		return (TRUE);
	return (FALSE);
}