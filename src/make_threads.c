/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:08:05 by amagnan           #+#    #+#             */
/*   Updated: 2019/12/17 20:10:39 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int					check_obstructing_object_before_light(t_rt *rt,\
				t_ray shadow_ray, t_light *current_light, t_vec hitpoint)
{
	t_object	*new_closest_object;
	double		new_distance;

	new_closest_object = NULL;
	new_distance = INFINITY;
	if (!find_closest_intersected_object(rt, &shadow_ray,\
	&new_closest_object, &new_distance)
	|| (find_closest_intersected_object(rt, &shadow_ray, &new_closest_object,\
	&new_distance) && (new_distance >
	vec_magnitude(vec_sub(current_light->pos, hitpoint)))))
		return (1);
	return (0);
}

void				rt_main_thread_too(t_rt *rt, void *fun4)
{
	rt->thread[3].thread = SDL_CreateThread(fun4, "thread4", (void*)rt);
	SDL_WaitThread(rt->thread[3].thread, NULL);
}

void				rt_main_thread(t_rt *rt, void *fun1, void *fun2, void *fun3)
{
	rt->thread[0].thread = SDL_CreateThread(fun1, "thread1", (void*)rt);
	rt->thread[1].thread = SDL_CreateThread(fun2, "thread2", (void*)rt);
	rt->thread[2].thread = SDL_CreateThread(fun3, "thread3", (void*)rt);
	SDL_WaitThread(rt->thread[0].thread, NULL);
	SDL_WaitThread(rt->thread[1].thread, NULL);
	SDL_WaitThread(rt->thread[2].thread, NULL);
}

void				get_primary_ray_info(t_rt *rt, t_ray *ray)
{
	int		pix_screen_x;
	int		pix_screen_y;
	double	pix_camera_x;
	double	pix_camera_y;
	double	image_ratio;

	pix_screen_x = (ray->pix_nb % WIDTH);
	pix_screen_y = (ray->pix_nb / WIDTH);
	image_ratio = (double)(WIDTH / HEIGHT);
	pix_camera_x = (2.0 * (pix_screen_x + 0.5) /
	(double)WIDTH - 1) * image_ratio * SCALE;
	pix_camera_y = (1.0 - 2.0 * (pix_screen_y + 0.5) / (double)HEIGHT) * SCALE;
	ray->ray_o = vec_x_mat(vec_new(0, 0, 0), rt->cam_matrix);
	ray->ray_d = dir_x_mat(vec_new(pix_camera_x, pix_camera_y, -1),
	rt->cam_matrix);
	ray->ray_d = vec_normalize(ray->ray_d);
	ray->depth = -1;
	ray->ray_type = PRIMARY_RAY;
	ray->pix_color = rt->win.d_background[ray->pix_nb];
}

void				rt_render(t_rt *rt)
{
	rt_main_thread(rt, rt_thread_1, rt_thread_2, rt_thread_3);
	rt_main_thread_too(rt, rt_thread_4);
}
