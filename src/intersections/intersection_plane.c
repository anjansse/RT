#include "RT.h"

/*
** ----------------------------------------------------------------------------
**	If the denominator is (close to) zero, then it means that the ray is \
**	parallel to the plane and thus, we consider there is no intersection \
**	in this case.
**	See implementation details here:
**	https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-\
**	tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
**
**	@param {p0} is the point on the plane the closest to the origin (0, 0, 0)
** ----------------------------------------------------------------------------
*/

bool			find_intersection_plane(t_ray *ray, t_object *obj, double *object_dist)
{
	double	denominator;
	double	numerator;
	double	intersection_dist;
	t_vec	p0;

	*object_dist = INFINITY;
	denominator = vec_dot_product(RAY_D, PLANE->normal);
	if (denominator > EPSILON || denominator < -EPSILON)
	{
		vec_set(&p0, PLANE->normal.x * PLANE->dist_to_origin, \
						PLANE->normal.y * PLANE->dist_to_origin, \
						PLANE->normal.z * PLANE->dist_to_origin);
		numerator = vec_dot_product(vec_sub(p0, RAY_O), PLANE->normal);
		intersection_dist = numerator / denominator;
		if (intersection_dist > EPSILON && intersection_dist < *object_dist)
			*object_dist = intersection_dist;
	}
	if (*object_dist != INFINITY)
		return (TRUE);
	return (FALSE);
}