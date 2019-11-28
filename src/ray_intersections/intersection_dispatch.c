#include "RT.h"

/*
** ----------------------------------------------------------------------------
** Dispatch table containing ELEM nunber of possible elements, and their 
** corresponding quadratic function. We don't consider here the camera and 
** the light elements, hence the ELEM - 2
** ----------------------------------------------------------------------------
*/

t_disp_intersection		g_disp_intersection[NB_OBJECTS] = {
	{NB_SPHERE,	&find_intersection_sphere},
	{NB_PLANE, &find_intersection_plane},
	{NB_CYLINDER, &find_intersection_cylinder},
	{NB_CONE, &find_intersection_cone},
};

/*
** ----------------------------------------------------------------------------
** Solves a quadratic expression, i.e. a*x*x + b*x + c == 0.
** The function will return 1 is the equation has one or 2 solutions,
** and 0 otherwise.
**
** @param {double*} sols will contain the solutions of the equation if they exist,
** this pointer should point to a memory area that can contain 2 floats,
** corresponding to the 2 possible solutions.
** If there is just one solution, then the 2 memory slots will have the same value.
** ----------------------------------------------------------------------------
*/

bool			solve_quadratic_equa(double a, double  b, double c, double *sols)
{
	double	disc;
	double	q;

	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (FALSE);
	else if (disc == 0)
	{
		sols[0] = -0.5 * b / a;
		sols[1] = -0.5 * b / a;
	}
	else
	{
		q = (b > 0) ? -0.5 * (b + sqrt(disc)) : -0.5 * (b - sqrt(disc));
		sols[0] = q / a;
		sols[1] = c / q;
	}
	return (TRUE);
}

/*
** ----------------------------------------------------------------------------
**	The default values for the coefs elements is so that the quadratic solution \
**	would not find solutions (disc < 0 in this case) of there is no entree \
**	corresponding to this object type in the below dispatch table.
** ----------------------------------------------------------------------------
*/

// change the value ELEM - 2 by something more explicit

bool			check_intersection_with_specific_object(t_ray *ray, \
															t_object *object, \
															double *object_dist)
{
	bool	flag_intersect;
	int		i;

	
	flag_intersect = FALSE;
	i = -1;
	while (++i < NB_OBJECTS)
		if (object->type == g_disp_intersection[i].objType)
			flag_intersect = g_disp_intersection[i].function(ray, object, \
																object_dist);
	return (flag_intersect);
}

/*
** ----------------------------------------------------------------------------
**	This function checks if the current object is closer than the previously \
**	defined closest object.
**	N.B.: we don't consider distance that are below EPSILON to take into \
**	consideration the approximation in computer computation.
** ----------------------------------------------------------------------------
*/

bool			check_is_closest_object(double closest_object_dist, \
											double object_dist)
{
	if (object_dist > EPSILON && object_dist < closest_object_dist)
		return (TRUE);
	return (FALSE);
}

/*
** ----------------------------------------------------------------------------
** Thanks to ray direction and origin, this function will calculate any
** possible intersections between the primary ray and elements.
**
** @param {t_rt *} rt - Main structure for RT.
** ----------------------------------------------------------------------------
*/

bool			find_closest_intersected_object(t_rt *rt, t_ray *ray,
				t_object **closest_object, double *closest_object_dist)
{
	t_object	*object;
	double		object_dist;

	object = rt->obj;
	while (object)
	{
		if (TRUE == check_intersection_with_specific_object(ray, object,
																&object_dist))
			if (check_is_closest_object(*closest_object_dist, object_dist))
			{
				*closest_object = object;
				*closest_object_dist = object_dist;
			}
		object = object->next;
	}
	if (*closest_object_dist > EPSILON && *closest_object_dist != INFINITY)
		return (TRUE);
	return (FALSE);
<<<<<<< HEAD:src/ray_trace.c
}

// In this function, when calling the intersection functions, we could also pass
// to the functions the distance to the closest object ...

// void    	rt_trace_object_intersection(t_rt *rt, t_ray *ray)
// {
// 	double		closest_object_dist;
// 	t_object	*closest_object;

// 	closest_object_dist = INFINITY;
// 	closest_object = NULL;
// 	if (TRUE == find_closest_intersected_object(rt, ray, &closest_object, \
// 													&closest_object_dist))
// 	{
// 		if (closest_object->type == NB_SPHERE)
// 		{
// 			ray->pix_color = closest_object->sphere->color;
// 			ray->ray_type = END;
// 		}
// 		else if (closest_object->type == NB_PLANE)
// 		{
// 			ray->pix_color = closest_object->plane->color;
// 			ray->ray_type = END;
// 		}
// 	}
// 	else
// 		ray->ray_type = END;
// }

void    	rt_trace_object_intersection(t_rt *rt, t_ray *ray)
{
	t_vec		normal;
	double		facingRatio;
	double		closest_object_dist;
	t_object	*closest_object;
	t_vec hitpoint;

	closest_object_dist = INFINITY;
	closest_object = NULL;
	if (TRUE == find_closest_intersected_object(rt, ray, &closest_object, \
													&closest_object_dist))
	{
		if (ray->ray_type == LIGHT)
		{
			printf("Intersected object's type: %d\n", closest_object->type);
			ray->ray_type = END;
			ray->pix_color = 0x000000;
		}
		else
		{
			if (closest_object->type == NB_SPHERE)
			{
				hitpoint = vec_add(RAY_O, vec_scale(RAY_D, closest_object_dist));
				normal = vec_normalize(vec_sub(hitpoint, closest_object->sphere->center));
				if ((facingRatio = vec_dot_product(normal, vec_scale(rt->obj->light->dir, -1))) < 0)
					facingRatio = 0;
				ray->pix_color = ft_luminosity(closest_object->sphere->color, facingRatio);
				ray->ray_type = LIGHT;
				RAY_O = hitpoint;
				RAY_D = vec_scale(rt->obj->light->dir, -1);
			}
			else if (closest_object->type == NB_PLANE)
			{
				hitpoint = vec_add(RAY_O, vec_scale(RAY_D, closest_object_dist));
				normal = closest_object->plane->normal;
				if ((facingRatio = vec_dot_product(normal, vec_scale(rt->obj->light->dir, -1))) < 0) {
					facingRatio = -facingRatio; // facingRatio seems to be the inverse of the expected result for some reason
					// facingRatio = 0;
				}
				ray->pix_color = ft_luminosity(closest_object->plane->color, facingRatio);
				ray->ray_type = LIGHT;
				RAY_O = vec_sub(hitpoint, vec_scale(normal, 0.0001));
				RAY_D = vec_scale(rt->obj->light->dir, -1);
			}
		}
	}
	else
		ray->ray_type = END;
=======
>>>>>>> bed65ecd15d2eeb95116e624837356168fb8182f:src/ray_intersections/intersection_dispatch.c
}