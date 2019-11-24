#include "RT.h"

void			rt_info_primary_ray(t_rt *rt, t_ray *ray)
{
	int      pix_screen_x;
	int      pix_screen_y;
	double   pix_camera_x;
	double   pix_camera_y;
	double   image_ratio;
	
	pix_screen_x = (ray->pix_nb % WIDTH);
	pix_screen_y = (ray->pix_nb / WIDTH);
	image_ratio = (double)(WIDTH / HEIGHT);
	pix_camera_x = (2.0 * (pix_screen_x + 0.5) / (double)WIDTH - 1) * image_ratio * SCALE;
	pix_camera_y = (1.0 - 2.0 * (pix_screen_y + 0.5) / (double)HEIGHT) * SCALE;
	RAY_O = vec_x_mat(vec_new(0, 0, 0), CAM_MAT);
	RAY_D = dir_x_mat(vec_new(pix_camera_x, pix_camera_y, -1), CAM_MAT);
	RAY_D = vec_normalize(RAY_D);
}

void				rt_info_light_ray(t_rt *rt, t_ray *ray,
					t_object *closest_object, double closest_object_distance)
{
	t_vec		normal;
	double		facingRatio;
	t_vec		hitpoint;

	// hitpoint = vec_add(vec_scale(RAY_D, closes_object_distance), RAY_O);

	// if (closest_object->type == NB_SPHERE)
	// 	normal = vec_normalize(vec_sub(hitpoint, closest_object->sphere->center));
	// else
	// 	normal = closest_object->plane->normal;

	// if (closest_object->type == NB_SPHERE && (facingRatio = vec_dot_product(normal, vec_scale(rt->obj->light->dir, 1))) < 0)
	// 	facingRatio = 0;
	// if (closest_object->type == NB_PLANE && (facingRatio = vec_dot_product(normal, vec_scale(rt->obj->light->dir, 1))) < 0)
	// 	facingRatio = -facingRatio;
	// if (closest_object->type == NB_SPHERE)
	// 	ray->pix_color = ft_luminosity(closest_object->sphere->color, facingRatio);
	// else
	// 	ray->pix_color = ft_luminosity(closest_object->plane->color, facingRatio);
	

	// RAY_O = hitpoint;
	// RAY_D = vec_scale(rt->obj->light->dir, -1);
	// ray->ray_type = LIGHT;


	if (closest_object->type == NB_SPHERE)
	{
		hitpoint = vec_add(RAY_O, vec_scale(RAY_D, closest_object_distance));
		normal = vec_normalize(vec_sub(hitpoint, closest_object->sphere->center));
		if ((facingRatio = vec_dot_product(normal, vec_scale(rt->obj->light->dir, -1))) < 0)
			facingRatio = 0;
		ray->pix_color = ft_luminosity(closest_object->sphere->color, facingRatio);
		ray->ray_type = LIGHT;
		RAY_O = hitpoint;
		RAY_D = vec_sub(rt->obj->light->pos, hitpoint);
	}
	else if (closest_object->type == NB_PLANE)
	{
		hitpoint = vec_add(RAY_O, vec_scale(RAY_D, closest_object_distance));
		normal = closest_object->plane->normal;
		if ((facingRatio = vec_dot_product(vec_scale(normal, -1), vec_scale(rt->obj->light->dir, -1))) < 0) {
			facingRatio = 0;
		}
		ray->pix_color = ft_luminosity(closest_object->plane->color, facingRatio);
		ray->ray_type = LIGHT;
		RAY_O = vec_sub(hitpoint, vec_scale(normal, 0.0001));
		RAY_D = vec_sub(rt->obj->light->pos, hitpoint);
	}

}

void				rt_info_refraction_ray(t_rt *rt, t_ray *ray)
{
	(void)rt;
	(void)ray;
}

void				rt_info_reflection_ray(t_rt *rt, t_ray *ray)
{
	(void)rt;
	(void)ray;
}
