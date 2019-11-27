#include "RT.h"

# define                MAX_Y (CYLINDER->center.y + (CYLINDER->height / 2))
# define                MIN_Y (CYLINDER->center.y - (CYLINDER->height / 2))

static void            find_quadratic_equa_coefs_cylinder(t_ray *ray, t_object *obj, double *coefs)
{
    coefs[0] = (RAY_D.x * RAY_D.x) + (RAY_D.z * RAY_D.z);
    coefs[1] = 2 * (RAY_O.x * RAY_D.x + RAY_O.z * RAY_D.z);
    coefs[2] = RAY_O.x * RAY_O.x + RAY_O.z * RAY_O.z - CYLINDER->radius * CYLINDER->radius;
}

bool			find_intersection_cylinder(t_ray *ray, t_object *obj, double *object_dist)
{
    double      coefs[3];
    double      sols[2];
    double      z[2];

    *object_dist = INFINITY;
    find_quadratic_equa_coefs_cylinder(ray, obj, coefs);
    if (TRUE == solve_quadratic_equa(coefs[0], coefs[1], coefs[2], sols))
    {
        z[0] = RAY_O.y + RAY_D.y * sols[0];
        z[1] = RAY_O.y + RAY_D.y * sols[1];

        if (z[0] > MIN_Y && z[0] < MAX_Y && sols[0] > EPSILON && sols[0] < *object_dist)
			*object_dist = sols[0];
		if (z[1] > MIN_Y && z[1] < MAX_Y && sols[1] > EPSILON && sols[1] < *object_dist)
			*object_dist = sols[1];
        // Need to find a way to get the caps at the top and bottom
    }       
    if (*object_dist != INFINITY)
		return (TRUE);
	return (FALSE);
}