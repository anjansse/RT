#include "RT.h"

static void 		rt_ray_info(t_rt *rt, t_ray *ray)
{
	if (ray->ray_type == PRIMARY)
		rt_info_primary_ray(rt, ray);
	else if (ray->ray_type == LIGHT)
		rt_info_light_ray(rt, ray);
	else if (ray->ray_type == REFRACTION)
		rt_info_refraction_ray(rt, ray);
	else if (ray->ray_type == REFLECTION)
		rt_info_reflection_ray(rt, ray);
}

static void			rt_ray_trace(t_rt *rt, t_ray *ray)
{
	if (ray->ray_type == PRIMARY || ray->ray_type == LIGHT)
		rt_trace_object_intersection(rt, ray);
}

static void				rt_cast_specific_ray(t_rt *rt)
{
	int	iteration_nb;
	t_ray	current_ray;

	// printf("went through: %d\n", rt->pix);
	iteration_nb = 0;
	current_ray.ray_type = PRIMARY;
	current_ray.pix_color = DEFAULT_BACKGROUND[rt->pix];
	while (1)
	{
		if (iteration_nb == MAX_ITERATION || current_ray.ray_type == END)
			break ;
		rt_ray_info(rt, &current_ray);
		rt_ray_trace(rt, &current_ray);
		++iteration_nb;
	}
	FRAMEBUFF[rt->pix] = current_ray.pix_color;
}

/*
** ----------------------------------------------------------------------------
** Main printing function for the scene, parses all the pixels and casts rays
** through them to check for intersection with objects, and get informations
** on light, shadows and overall shade applied on the color of said object.
**
** @param {t_rt *} rt - Main structure for RT.
** ----------------------------------------------------------------------------
*/

void            rt_cast_rays(t_rt *rt)
{
	int		i;

	i = -1;
	while (++i < (HEIGHT * WIDTH))
	{
		rt->pix = i;
		rt_cast_specific_ray(rt);
	}
}
