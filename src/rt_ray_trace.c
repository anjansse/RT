#include "RT.h"

/*
** ----------------------------------------------------------------------------
** Dispatch table containing ELEM nunber of possible elements, and their corresponding quadratic function.
**	We don't consider here the camera and the light elements, hence the ELEM - 2
** ----------------------------------------------------------------------------
*/

t_dis_intersection		g_dis_quad_table[ELEM - 2] = {
	{NB_SPHERE, &find_quad_equ_coefs_sphere},
};

/*
** ----------------------------------------------------------------------------
** The functions below allow to determine the coefs of the quadratic equation 
** to solve in order to find the intersection points between the object and 
** the ray at hand.
** ----------------------------------------------------------------------------
*/

void			find_quad_equ_coefs_sphere(t_ray *ray, t_object *obj, double *coefs)
{

		coefs[0] = vec_dot_product(RAY_D, RAY_D);
		coefs[1] = 2 * vec_dot_product(RAY_D, vec_sub(RAY_O, SPHERE->center));
		coefs[2] = vec_dot_product(vec_sub(RAY_O, SPHERE->center), \
									vec_sub(RAY_O, SPHERE->center))\
					- SPHERE->radius * SPHERE->radius;
}

/*
** ----------------------------------------------------------------------------
** Solves a quadratic expression, i.e. a*x*x + b*x + c == 0.
** The function will return 1 is the equation has one or 2 solutions, \
** and 0 otherwise.
**
** @param {double*} sols will contain the solutions of the equation if they exist,
** this pointer should point to a memory area that can contain 2 floats, \
** corresponding to the 2 possible solutions.
** If there is just one solution, then the 2 memory slots will have the same value.
** ----------------------------------------------------------------------------
*/

bool			solve_quadratic(double a, double  b, double c, double *sols)
{
	double	disc;
	double	q;
	double	tmp;

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
		if (sols[1] > sols[0])
		{
			tmp = sols[0];
			sols[0] = sols[1];
			sols[1] = tmp;
		}
	}
	return (TRUE);
}

/*
** ----------------------------------------------------------------------------
** Thanks to ray direction and origin, this function will calculate any
** possible intersections between the primary ray and elements.
**
** @param {t_rt *} rt - Main structure for RT.
** ----------------------------------------------------------------------------
*/

// Should we integrate some epsilon here?
// When updating the mean we do > 0, should we do >= 0

// We should return a t_sphere* with the value NULL if no sphere is intersected.
// and the address of the closest sphere otherwise.
// alternatively we should return the min distance.
// alternatively we should return a 

// CAREFUL: the ray_direction vector has to be normalized before entering 
// this function, otherwise we probably express the length the proportionnaly to 
// the vector length and not to the unit value

bool			check_is_closest_object(double *dist, double *sols)
{
	bool val;
	
	val = FALSE;
	if (sols[0] > 0 && sols[0] < *dist)
	{
		*dist = sols[0];
		val = TRUE;
	}
	if (sols[1] > 0 && sols[1] < *dist)
	{
		*dist = sols[1];
		val = TRUE;
	}
	return (val);
}

bool			intersection_object(t_rt *rt, t_ray *ray, t_object **closestObject, double *dist)
{
	t_object	*object;
	double		coefs[3];
	double		sols[2];
	int			i;

	object = rt->obj;
	while (object)
	{
		i = -1;
		coefs[0] = 1;
		coefs[1] = 0;
		coefs[2] = 1;
		
		while (++i < ELEM - 2)
			if (object->type == g_dis_quad_table[i].objType)
				g_dis_quad_table[i].function(ray, object, coefs);
		if (TRUE == solve_quadratic(coefs[0], coefs[1], coefs[2], sols))
			if (check_is_closest_object(dist, sols))
				*closestObject = object;
		object = object->next;
	}

	if (*dist > 0.0 && *dist != INFINITY)
		return (TRUE);
	return (FALSE);
}

// In this function, when calling the intersection functions, we could also pass
// to the functions the distance to the closest object ...

// void    	rt_trace_object_intersection(t_rt *rt, t_ray *ray)
// {
// 	t_object	*closest_object;
// 	double		dist_closest_object;

// 	closest_object = NULL;
// 	dist_closest_object = INFINITY;
// 	if (TRUE == intersection_object(rt, ray, &closest_object, &dist_closest_object))
// 	{
// 		if (closest_object->type == NB_SPHERE)
// 		{
// 			ray->pix_color = closest_object->sphere->color;
// 			ray->ray_type = END;
// 		}
// 	}
// 	else
// 	{
// 		ray->ray_type = END;
// 	}
	
// }

uint32_t		ft_luminosity(uint32_t color, double scale)
{
	double		r;
	double		g;
	double		b;
	r = (((color & 16711680) >> 16) * scale);
	g = (((color & 65280) >> 8) * scale);
	b = ((color & 255) * scale);
	return (ft_rgb((uint8_t)r, (uint8_t)g, (uint8_t)b));
}

void    	rt_trace_object_intersection(t_rt *rt, t_ray *ray)
{
	t_object	*closest_object;
	double		dist_closest_object;
	t_vec		normal;
	double		facingRatio;

	closest_object = NULL;
	dist_closest_object = INFINITY;
	if (TRUE == intersection_object(rt, ray, &closest_object, &dist_closest_object))
	{
		if (ray->ray_type == LIGHT)
		{
			ray->ray_type = END;
			ray->pix_color = 0x000000;
		}
		else
		{
			RAY_D = vec_scale(RAY_D, dist_closest_object);
			RAY_D = vec_add(RAY_O, RAY_D);
			normal = vec_normalize(vec_sub(RAY_D, closest_object->sphere->center));
			
			if ((facingRatio = vec_dot_product(normal, vec_scale(rt->obj->light->dir, -1))) < 0)
				facingRatio = 0;
			ray->ray_type = LIGHT;
			ray->pix_color = ft_luminosity(closest_object->sphere->color, facingRatio);
		}
	}
	else
		ray->ray_type = END;
	
}