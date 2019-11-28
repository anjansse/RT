#include "RT.h"

/*
** ----------------------------------------------------------------------------
**
** ----------------------------------------------------------------------------
*/

static void			sphere_shadow_ray_info(t_rt *rt, t_ray *ray,
t_object *closest_object, double closest_object_distance)
{
	t_vec		normal;
	double		facingRatio;
	t_vec		hitpoint;

	hitpoint = vec_add(RAY_O, vec_scale(RAY_D, closest_object_distance));
	normal = vec_normalize(vec_sub(hitpoint, closest_object->sphere->center));

	RAY_D = vec_normalize(vec_sub(rt->obj->light->pos, hitpoint));
	// RAY_D = vec_scale(rt->obj->light->dir, -1);

	if ((facingRatio = vec_dot_product(normal, RAY_D)) < 0)
		facingRatio = 0;
	ray->pix_color = ft_luminosity(closest_object->sphere->color, facingRatio);
	ray->ray_type = SHADOW_RAY;
	RAY_O = hitpoint;
}

/*
** ----------------------------------------------------------------------------
**
** ----------------------------------------------------------------------------
*/

static void			plane_shadow_ray_info(t_rt *rt, t_ray *ray,
t_object *closest_object, double closest_object_distance)
{
	t_vec		normal;
	double		facingRatio;
	t_vec		hitpoint;
	
	hitpoint = vec_add(RAY_O, vec_scale(RAY_D, closest_object_distance));
	normal = vec_scale(closest_object->plane->normal, -1); 						// selon le cas

	RAY_D = vec_normalize(vec_sub(rt->obj->light->pos, hitpoint));
	// RAY_D = vec_scale(rt->obj->light->dir, -1);

	if ((facingRatio = vec_dot_product(normal, RAY_D)) < 0)
		facingRatio = 0;
	ray->pix_color = ft_luminosity(closest_object->plane->color, facingRatio);
	ray->ray_type = SHADOW_RAY;
	RAY_O = vec_sub(hitpoint, vec_scale(normal, 0.0001));
}

/*
** ----------------------------------------------------------------------------
**
** ----------------------------------------------------------------------------
*/

static void			cylinder_shadow_ray_info(t_rt *rt, t_ray *ray,
t_object *closest_object, double closest_object_distance)
{
	t_vec		normal;
	double		facingRatio;
	t_vec		hitpoint;
	
	hitpoint = vec_add(RAY_O, vec_scale(RAY_D, closest_object_distance));
	normal = vec_normalize(vec_sub(hitpoint, vec_new(closest_object->cylinder->base.x, hitpoint.y, closest_object->cylinder->base.z)));

	RAY_D = vec_normalize(vec_sub(rt->obj->light->pos, hitpoint));
	// RAY_D = vec_scale(rt->obj->light->dir, -1);

	// if (vec_dot_product(normal, RAY_D) < 0)									// selon le cas
	// 	normal = vec_scale(normal, -1);

	if ((facingRatio = vec_dot_product(normal, RAY_D)) < 0)
		facingRatio = 0;
	ray->pix_color = ft_luminosity(closest_object->cylinder->color, facingRatio);
	ray->ray_type = SHADOW_RAY;
	RAY_O = hitpoint;
}

/*
** ----------------------------------------------------------------------------
**
** ----------------------------------------------------------------------------
*/

static void			cone_shadow_ray_info(t_rt *rt, t_ray *ray, t_object *closest_object, double closest_object_distance)
{
	t_vec		normal;
	double		facingRatio;
	t_vec		hitpoint;

	hitpoint = vec_add(RAY_O, vec_scale(RAY_D, closest_object_distance));
	normal = vec_normalize(vec_sub(hitpoint, vec_new(closest_object->cone->cone_tips.x, hitpoint.y, closest_object->cone->cone_tips.z)));	// I don't think it is the right way to get the normal
	RAY_D = vec_normalize(vec_sub(rt->obj->light->pos, hitpoint));
	if ((facingRatio = vec_dot_product(normal, RAY_D)) < 0)
		facingRatio = 0;
	ray->pix_color = ft_luminosity(closest_object->cone->color, facingRatio);
	ray->ray_type = SHADOW_RAY;
	RAY_O = hitpoint;
}

/*
** ----------------------------------------------------------------------------
**
** ----------------------------------------------------------------------------
*/

void				get_shadow_ray_info(t_rt *rt, t_ray *ray,
					t_object *closest_object, double closest_object_distance)
{
	if (closest_object->type == NB_SPHERE)
		sphere_shadow_ray_info(rt, ray, closest_object, closest_object_distance);
	else if (closest_object->type == NB_PLANE)
		plane_shadow_ray_info(rt, ray, closest_object, closest_object_distance);
	else if (closest_object->type == NB_CYLINDER)
		cylinder_shadow_ray_info(rt, ray, closest_object, closest_object_distance);
	else if (closest_object->type == NB_CONE)
		cone_shadow_ray_info(rt, ray, closest_object, closest_object_distance);
}