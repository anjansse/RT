/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:08:05 by amagnan           #+#    #+#             */
/*   Updated: 2019/12/17 12:42:49 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

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

void			get_primary_ray_info(t_rt *rt, t_ray *ray)
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
	ray->depth = -1;
	ray->ray_type = PRIMARY_RAY;
	ray->pix_color = DEFAULT_BACKGROUND[ray->pix_nb];
}

void				rt_render(t_rt *rt)
{
	rt_main_thread(rt, rt_thread_1, rt_thread_2, rt_thread_3);
	rt_main_thread_too(rt, rt_thread_4);
}