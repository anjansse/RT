#include "RT.h"

# define                MIN_X CYLINDER->base.x
# define                MIN_Y CYLINDER->base.y
# define                MIN_Z CYLINDER->base.z
# define                MAX_X (CYLINDER->base.x + CYLINDER->height)
# define                MAX_Y (CYLINDER->base.y + CYLINDER->height)
# define                MAX_Z (CYLINDER->base.z + CYLINDER->height)

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
    // double      x[2];
    // double      y[2];
    // double      z[2];

    *object_dist = INFINITY;
    find_quadratic_equa_coefs_cylinder(ray, obj, coefs);
    if (TRUE == solve_quadratic_equa(coefs[0], coefs[1], coefs[2], sols))
    {
        // x[0] = RAY_O.x + RAY_D.x * sols[0];
        // x[1] = RAY_O.x + RAY_D.x * sols[1];
        // y[0] = RAY_O.y + RAY_D.y * sols[0];
        // y[1] = RAY_O.y + RAY_D.y * sols[1];
        // z[0] = RAY_O.z + RAY_D.z * sols[0];
        // z[1] = RAY_O.z + RAY_D.z * sols[1];

        // if (CYLINDER->direction.x > 0) {
        //     if (x[0] > MIN_X && x[0] < MAX_X && sols[0] < *object_dist)
        //         *object_dist = sols[0];
        //     if (x[1] > MIN_X && x[1] < MAX_X && sols[1] < *object_dist)
        //         *object_dist = sols[1];
        // } else if (CYLINDER->direction.y > 0) {
        //     if (y[0] > MIN_Y && y[0] < MAX_Y && sols[0] < *object_dist)
        //         *object_dist = sols[0];
        //     if (y[1] > MIN_Y && y[1] < MAX_Y && sols[1] < *object_dist)
        //         *object_dist = sols[1];
        // } else if (CYLINDER->direction.z > 0) {
        //     if (z[0] > MIN_Z && z[0] < MAX_Z && sols[0] < *object_dist)
        //         *object_dist = sols[0];
        //     if (z[1] > MIN_Z && z[1] < MAX_Z && sols[1] < *object_dist)
        //         *object_dist = sols[1];
        // }
        if (sols[0] > EPSILON && sols[0] < *object_dist)
			*object_dist = sols[0];
		if (sols[1] > EPSILON && sols[1] < *object_dist)
			*object_dist = sols[1];

        // Need to find a way to get the caps at the top and bottom
        // ->   it's written on your website https://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html#eqn:rectray
    }       
    if (*object_dist != INFINITY)
		return (TRUE);
	return (FALSE);
}