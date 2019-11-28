#include "RT.h"

# define OBJ_TYPE				closest_object->type
# define INTERSECTION_OBJ		(TRUE == find_closest_intersected_object(rt, ray,\
								&closest_object, &closest_object_dist))
/*
** ----------------------------------------------------------------------------
** Thanks to ray direction and origin, this function will calculate any
** possible intersections between the primary ray and elements.
**
** @param {t_rt *} rt - Main structure for RT.
** ----------------------------------------------------------------------------
*/

static void	apply_shadow(t_rt *rt, t_ray *ray)
{
	RAY_TYPE = END_RAY;
	ray->pix_color = 0x000000;
	rt_cast_ray(rt, ray);
}

void    	rt_ray_dispatching(t_rt *rt, t_ray *ray)
{
	double		closest_object_dist;
	t_object	*closest_object;

	closest_object_dist = INFINITY;
	closest_object = NULL;
	if (INTERSECTION_OBJ)
	{
		// if (closest_object->type == NB_CONE)
			// printf("ray_type: %c\n")
		if (RAY_TYPE == PRIMARY_RAY)
		{
			get_shadow_ray_info(rt, ray, closest_object, closest_object_dist);
			rt_cast_ray(rt, ray);
		}
		else if (RAY_TYPE == SHADOW_RAY)
			apply_shadow(rt, ray);
	}
	else
		RAY_TYPE = END_RAY;
}