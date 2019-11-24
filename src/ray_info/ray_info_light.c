#include "RT.h"

/*
**
*/

static void			sphere_shadow_ray_info(t_rt *rt, t_ray *ray,
t_object *closest_object, double closest_object_distance)
{
	t_vec		normal;
	double		facingRatio;
	t_vec		hitpoint;

	hitpoint = vec_add(RAY_O, vec_scale(RAY_D, closest_object_distance));
	normal = vec_normalize(vec_sub(hitpoint, closest_object->sphere->center));
	if ((facingRatio = vec_dot_product(normal, vec_scale(rt->obj->light->dir, -1))) < 0)
		facingRatio = 0;
	ray->pix_color = ft_luminosity(closest_object->sphere->color, facingRatio);
	ray->ray_type = SHADOW_RAY;
	RAY_O = hitpoint;
	RAY_D = vec_sub(rt->obj->light->pos, hitpoint);
}

/*
**
*/

static void			plane_shadow_ray_info(t_rt *rt, t_ray *ray,
t_object *closest_object, double closest_object_distance)
{
	t_vec		normal;
	double		facingRatio;
	t_vec		hitpoint;
	
	hitpoint = vec_add(RAY_O, vec_scale(RAY_D, closest_object_distance));
	normal = closest_object->plane->normal;
	if ((facingRatio = vec_dot_product(vec_scale(normal, -1), vec_scale(rt->obj->light->dir, -1))) < 0) {
		facingRatio = 0;
	}
	ray->pix_color = ft_luminosity(closest_object->plane->color, facingRatio);
	ray->ray_type = SHADOW_RAY;
	RAY_O = vec_sub(hitpoint, vec_scale(normal, 0.0001));
	RAY_D = vec_sub(rt->obj->light->pos, hitpoint);
}

/*
**
*/

void				get_shadow_ray_info(t_rt *rt, t_ray *ray,
					t_object *closest_object, double closest_object_distance)
{
	if (closest_object->type == NB_SPHERE)
		sphere_shadow_ray_info(rt, ray, closest_object, closest_object_distance);
	else if (closest_object->type == NB_PLANE)
		plane_shadow_ray_info(rt, ray, closest_object, closest_object_distance);
}