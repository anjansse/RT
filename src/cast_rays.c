#include "RT.h"

# define INTERSECTION_OBJ		(TRUE == find_closest_intersected_object(rt, ray,\
								&closest_object, &closest_object_distance))

t_vec			get_hitpoint(t_ray *ray, double closest_object_distance)
{
	return (vec_add(RAY_O, vec_scale(RAY_D, closest_object_distance)));
}

t_vec			get_normal_intersection_sphere(t_ray *ray,
												t_object *closest_object,
												t_vec hitpoint)
{
	t_vec normal;

	normal = vec_normalize(vec_sub(hitpoint, closest_object->sphere->center));
	return (normal);
	(void)ray;
}

t_vec			get_normal_intersection_plane(t_ray *ray,
												t_object *closest_object)
{
	t_vec normal;
	if (vec_dot_product(RAY_D, closest_object->plane->normal) > 0)
		normal = vec_scale(closest_object->plane->normal, -1);
	else
		normal = closest_object->plane->normal;
	return (normal);
}

// t_vec			get_normal_intersection_cylinder(t_ray *ray,
// 													t_object *closest_object,
// 													t_vec hitpoint)
// {
// 	t_vec normal;
// 	t_vec new_vec;

// 	new_vec = vec_new(hitpoint.x,
// 						closest_object->cylinder->base.y, closest_object->cylinder->base.z);
// 	normal = vec_normalize(vec_sub(hitpoint, new_vec));
// 	return (normal);
// 	(void)ray;
// }

t_vec			get_normal_intersection_cylinder(t_ray *ray,
										t_object *closest_object,
										t_vec hitpoint)
{
	t_vec	normal;
	t_vec	new_vec;
	double	scale;
	scale = vec_dot_product(hitpoint, closest_object->cylinder->direction);
	scale -= vec_dot_product(closest_object->cylinder->base,
								closest_object->cylinder->direction);
	scale /= vec_dot_product(closest_object->cylinder->direction,
								closest_object->cylinder->direction);
	new_vec = vec_scale(closest_object->cylinder->direction, scale);
	new_vec = vec_add(new_vec, closest_object->cylinder->base);
	normal = vec_normalize(vec_sub(hitpoint, new_vec));
	return (normal);
	(void)ray;
}


t_vec			get_normal_intersection_cone(t_ray * ray,
												t_object *closest_object,
												t_vec hitpoint)
{
	t_vec normal;
	t_vec new_vec;

	new_vec = vec_new(closest_object->cone->cone_tips.x,
						hitpoint.y, closest_object->cone->cone_tips.z);
	normal = vec_normalize(vec_sub(hitpoint, new_vec));
	return (normal);
	(void)ray;
}

t_vec			get_normal_at_hitpoint(t_ray *ray, t_object *closest_object,
										t_vec hitpoint)
{
	t_vec normal;

	normal = vec_new(0,0,0);
	if (closest_object->type == NB_SPHERE)
		normal = get_normal_intersection_sphere(ray, closest_object, hitpoint);
	else if (closest_object->type == NB_PLANE)
		normal = get_normal_intersection_plane(ray, closest_object);
	else if (closest_object->type == NB_CYLINDER)
		normal = get_normal_intersection_cylinder(ray, closest_object, hitpoint);
	else if (closest_object->type == NB_CONE)
		normal = get_normal_intersection_cone(ray, closest_object, hitpoint);
	
	return (normal);
}

// BELOW FUNCTION:
// for each light, see if they are obstructed by an object
// if not, then compute their contribution to the color
// add all these contributions (or more complex mixing technic

uint32_t		ft_add(uint32_t color1, uint32_t color2, uint32_t max)
{
	double		r;
	double		g;
	double		b;
	double		maxr;
	double		maxg;
	double		maxb;
	
	r = (((color1 & 0xff0000) >> 16) + ((color2 & 0xff0000) >> 16));
	g = (((color1 & 0x00ff00) >> 8) + ((color2 & 0x00ff00) >> 8));
	b = ((color1 & 0x0000ff) + (color2 & 0x0000ff));
	maxr = (max & 0xff0000) >> 16;
	maxg = (max & 0x00ff00) >> 8;
	maxb = (max & 0x0000ff);
	if (r > maxr)
		r = maxr;
	if (g > maxg)
		g = maxg;
	if (b > maxb)
		b = maxb;
	return (ft_rgb((uint8_t)r, (uint8_t)g, (uint8_t)b));
}

static int			check_material(t_object *closest_object, int material)
{
	if (closest_object->type == NB_CONE)
	{
		if (closest_object->cone->material == material)
			return 1;
	}
	else if (closest_object->type == NB_CYLINDER)
	{
		if (closest_object->cylinder->material == material)
			return 1;
	}
	else if (closest_object->type == NB_PLANE)
	{
		if (closest_object->plane->material == material)
			return 1;
	}
	else if (closest_object->type == NB_SPHERE)
	{
		if (closest_object->sphere->material == material)
			return 1;
	}
	return 0;
}

uint32_t		calculate_scalar(uint32_t color, double delta_intensity)
{
	double old_r;
	double old_g;
	double old_b;
	double r;
	double g;
	double b;
	double mult_intesity;

	mult_intesity = 100000 - delta_intensity * 100000;
	old_r = (color & 0xff0000) >> 16;
	old_g = (color & 0x00ff00) >> 8;
	old_b = (color & 0x0000ff);

	r = (double)(255 - old_r) / 1500;
	r = 255 - (r * mult_intesity);
	g = (double)(255 - old_g) / 1500;
	g = 255 - (g * mult_intesity);
	b = (double)(255 - old_b) / 1500;
	b = 255 - (b * mult_intesity);
	return (ft_rgb((unsigned char)r, (unsigned char)g, (unsigned char)b));
}

t_color			define_and_cast_shadow_rays(t_rt *rt, t_ray *ray,\
												t_object *closest_object,
												double closest_object_distance)
{
	t_ray		shadow_ray;
	t_vec		hitpoint;
	t_vec		normal;
	t_light		*current_light;
	double		facing_ratio;
	t_color		final_color;

	if (!check_material(closest_object, DIFFUSE))
		return ((t_color){0x000000, 0});

	hitpoint = get_hitpoint(ray, closest_object_distance);
	normal = get_normal_at_hitpoint(ray, closest_object, hitpoint);
	current_light = rt->light;

	final_color.color = 0x000000;
	final_color.intensity = 0;

	// Looping through all the lights and looking for intersections
	while (current_light)
	{
		// Getting the new ray direction and origin
		shadow_ray.ray_d = vec_normalize(vec_sub(current_light->pos, hitpoint));
		shadow_ray.ray_o = hitpoint;
		
		t_object		*new_closest_object = NULL;
		double			new_distance = INFINITY;

		// If intersection then it's in shadow so we don't do anything, else add color contribution
		if (!find_closest_intersected_object(rt, &shadow_ray, &new_closest_object, &new_distance)
		|| (find_closest_intersected_object(rt, &shadow_ray, &new_closest_object, &new_distance)
		&& (new_distance > vec_magnitude(vec_sub(current_light->pos, hitpoint)))))
		{
			// Getting the facing ratio (exposure to light source)
			if ((facing_ratio = vec_dot_product(normal, shadow_ray.ray_d)) < 0)
				facing_ratio = 0;

			final_color.intensity += current_light->intensity * facing_ratio;
			// Adding the color contributions. I cap the color value to the intersected object's original color for now.
			if (closest_object->type == NB_SPHERE)
				final_color.color = closest_object->sphere->color;
			else if (closest_object->type == NB_PLANE)
				final_color.color = closest_object->plane->color;
			else if (closest_object->type == NB_CYLINDER)
				final_color.color = closest_object->cylinder->color;
			else if (closest_object->type == NB_CONE)
				final_color.color = closest_object->cone->color;
			if (closest_object->type != NB_PLANE && facing_ratio >= 0.98500 && facing_ratio <= 1)
			{
				final_color.color = calculate_scalar(final_color.color, facing_ratio);
				final_color.intensity = 1;
			}
		}
		current_light = current_light->next;
	}

	return (final_color);
	
}

static uint8_t	average_color(t_color reflect, t_color refract, t_color scatter, int shift)
{
	double tot_color_composant;
	double tot_intensity;

	tot_color_composant = (double)((reflect.color & (0x00ff << shift)) >> shift) * reflect.intensity;
	tot_color_composant += (double)((refract.color & (0x00ff << shift)) >> shift) * refract.intensity; 
	tot_color_composant += (double)((scatter.color & (0x00ff << shift)) >> shift) * scatter.intensity;
	tot_intensity = reflect.intensity + refract.intensity + scatter.intensity;
	return ((uint8_t)(tot_color_composant / tot_intensity));
}

t_color			combine_colors(t_color reflection_color,
								t_color refraction_color,
								t_color scattering_color)
{
	// if (reflection_color.intensity != 0 || reflection_color.color != 0x000000)
	// 	return (reflection_color);
	// if (refraction_color.intensity != 0 || refraction_color.color != 0x000000)
	// 	return (refraction_color);
	// return (scattering_color);
	t_color color;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	// int total_weight;

	// total_weight = 0;
	// total_weight += (reflection_color.color & 0xff0000) >> 16 + (refraction_color.color & 0xff0000) >> 16 + (scattering_color.color & 0xff0000) >> 16;
	// total_weight += (reflection_color.color & 0x00ff00) >> 8 + (refraction_color.color & 0x00ff00) >> 8 + (scattering_color.color & 0x00ff00) >> 8;
	// total_weight += (reflection_color.color & 0x0000ff) + (refraction_color.color & 0x0000ff) + (scattering_color.color & 0x0000ff);
	// total_weight 

	color.intensity = reflection_color.intensity + refraction_color.intensity + scattering_color.intensity;
	if (color.intensity == 0)
		return ((t_color){0x000000, 0});
	r = average_color(reflection_color, refraction_color, scattering_color, 16);
	g = average_color(reflection_color, refraction_color, scattering_color, 8);
	b = average_color(reflection_color, refraction_color, scattering_color, 0);
	color.color = ft_rgb((uint8_t)r, (uint8_t)g, (uint8_t)b);
	color.intensity = reflection_color.intensity + refraction_color.intensity + scattering_color.intensity;
	
	return color;
}

t_color			define_and_cast_reflected_ray(t_rt *rt, t_ray *ray,\
												t_object *closest_object,
												double closest_object_distance)
{
	t_ray		reflection_ray;
	t_vec		hitpoint;
	t_vec		normal;
	t_color		color;

	hitpoint = get_hitpoint(ray, closest_object_distance);
	normal = get_normal_at_hitpoint(ray, closest_object, hitpoint);

	reflection_ray.depth = ++ray->depth;
	reflection_ray.pix_nb = ray->pix_nb;

	reflection_ray.ray_o = hitpoint;
	reflection_ray.ray_d = vec_sub(RAY_D, vec_scale(normal, 2 * vec_dot_product(RAY_D, normal))); 

	if (reflection_ray.depth < MAX_DEPTH)
	{
		if (closest_object->type == NB_SPHERE)
		{
			if (closest_object->sphere->material == REFLECTION)
			{
				color = rt_cast_ray(rt, &reflection_ray);
				return ((t_color){color.color, color.intensity * 0.8});
			}
		}
		else if (closest_object->type == NB_PLANE)
		{
			if (closest_object->plane->material == REFLECTION)
			{
				color = rt_cast_ray(rt, &reflection_ray);
				return ((t_color){color.color, color.intensity * 0.8});
			}
		}
		else if (closest_object->type == NB_CYLINDER)
		{
			if (closest_object->cylinder->material == REFLECTION)
			{
				color = rt_cast_ray(rt, &reflection_ray);
				return ((t_color){color.color, color.intensity * 0.8});
			}
		}
		else if (closest_object->type == NB_CONE)
		{
			if (closest_object->cone->material == REFLECTION)
			{
				color = rt_cast_ray(rt, &reflection_ray);
				return ((t_color){color.color, color.intensity * 0.8});
			}
		}
	}
	return ((t_color){0x000000, 0});
}

/*
** All formulas for refraction were found at:
** https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel.
*/

t_color			define_and_cast_refracted_ray(t_rt *rt, t_ray *ray, t_object *closest_object, double closest_object_distance)
{
	double c1;
	double c2;
	double nDelta;
	t_vec I;
	t_vec N;
	t_ray refraction_ray;

	refraction_ray.pix_nb = ray->pix_nb;
	refraction_ray.depth = ++ray->depth;

	refraction_ray.ray_o = get_hitpoint(ray, closest_object_distance);
	I = RAY_D;
	N = get_normal_at_hitpoint(ray, closest_object, refraction_ray.ray_o);
	nDelta = 1 / 1.3;
	c1 = vec_dot_product(N, I);
	c2 = sqrt(1 - (nDelta * nDelta) * (1 - (c1 * c1)));
	refraction_ray.ray_d = vec_sub(vec_scale((vec_add(I, vec_scale(N, c1))), nDelta), vec_scale(N, c2));
	
	if (refraction_ray.depth < MAX_DEPTH)
	{
		if (closest_object->type == NB_SPHERE)
		{
			if (closest_object->sphere->material == REFRACTION)
				// return rt_cast_ray(rt, &refraction_ray);
				return ((t_color){ft_luminosity((rt_cast_ray(rt, &refraction_ray).color), 0.8), 1});
		}
		else if (closest_object->type == NB_PLANE)
		{
			if (closest_object->plane->material == REFRACTION)
				return ((t_color){ft_luminosity((rt_cast_ray(rt, &refraction_ray).color), 0.8), 1});
				// return rt_cast_ray(rt, &refraction_ray);
		}
		else if (closest_object->type == NB_CYLINDER)
		{
			if (closest_object->cylinder->material == REFRACTION)
				// return rt_cast_ray(rt, &refraction_ray);
				return ((t_color){ft_luminosity((rt_cast_ray(rt, &refraction_ray).color), 0.8), 1});
		}
		else if (closest_object->type == NB_CONE)
		{
			if (closest_object->cone->material == REFRACTION)
				// return rt_cast_ray(rt, &refraction_ray);
				return ((t_color){ft_luminosity((rt_cast_ray(rt, &refraction_ray).color), 0.8), 1});
		}
	}
	return ((t_color){0x000000, 0});
}

/*
** ----------------------------------------------------------------------------
** Recursive function which casts a ray through the scene. Type of ray will
** influence what informations it will receive (ray_origin / ray_direction),
** and when a ray has hit it's target or is being casted too many times, 
** calls a shading function to color the pixel of which the ray is associated
** with.
**
** @param {t_rt *} rt - Main structure for RT.
** @param {t_ray *} ray - Ray that has to be casted from a point to another.
** ----------------------------------------------------------------------------
*/

t_color			rt_cast_ray(t_rt *rt, t_ray *ray)
{
	double		closest_object_distance;
	t_object	*closest_object;
	t_color		reflection_color;
	t_color		refraction_color;
	t_color		scattering_color;


	closest_object_distance = INFINITY;
	closest_object = NULL;
	if (INTERSECTION_OBJ)
	{
		reflection_color = define_and_cast_reflected_ray(rt, ray, closest_object, closest_object_distance);
		refraction_color = define_and_cast_refracted_ray(rt, ray, closest_object, closest_object_distance);
		scattering_color = define_and_cast_shadow_rays(rt, ray, closest_object, closest_object_distance);
		return (combine_colors(reflection_color, refraction_color,
								scattering_color));
	}
	else
		return ((t_color){DEFAULT_BACKGROUND[ray->pix_nb], 1});
}
