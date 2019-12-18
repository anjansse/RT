/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:14:01 by amagnan           #+#    #+#             */
/*   Updated: 2019/12/17 20:11:22 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int					rt_thread_1(void *data)
{
	int				i;
	t_ray			current_ray;
	t_color			pixel_color;
	t_rt			*rt;

	i = -1;
	rt = ((t_rt *)data);
	while ((current_ray.pix_nb = ++i) < (WIDTH * HEIGHT / 4))
	{
		get_primary_ray_info(rt, &current_ray);
		pixel_color = rt_cast_ray(rt, &current_ray);
		rt->win.framebuff[i] = ft_luminosity(pixel_color.color,
		pixel_color.intensity);
	}
	return (0);
}

int					rt_thread_2(void *data)
{
	int				i;
	t_ray			current_ray;
	t_color			pixel_color;
	t_rt			*rt;

	i = ((WIDTH * HEIGHT / 4) - 1);
	rt = ((t_rt *)data);
	while ((current_ray.pix_nb = ++i) < (WIDTH * HEIGHT / 4) * 2)
	{
		get_primary_ray_info(rt, &current_ray);
		pixel_color = rt_cast_ray(rt, &current_ray);
		rt->win.framebuff[i] = ft_luminosity(pixel_color.color,
		pixel_color.intensity);
	}
	return (0);
}

int					rt_thread_3(void *data)
{
	int				i;
	t_ray			current_ray;
	t_color			pixel_color;
	t_rt			*rt;

	i = ((WIDTH * HEIGHT / 4) * 2) - 1;
	rt = ((t_rt *)data);
	while ((current_ray.pix_nb = ++i) < (WIDTH * HEIGHT / 4) * 3)
	{
		get_primary_ray_info(rt, &current_ray);
		pixel_color = rt_cast_ray(rt, &current_ray);
		rt->win.framebuff[i] = ft_luminosity(pixel_color.color,
		pixel_color.intensity);
	}
	return (0);
}

int					rt_thread_4(void *data)
{
	int				i;
	t_ray			current_ray;
	t_color			pixel_color;
	t_rt			*rt;

	i = ((WIDTH * HEIGHT / 4) * 3) - 1;
	rt = ((t_rt *)data);
	while ((current_ray.pix_nb = ++i) < WIDTH * HEIGHT)
	{
		get_primary_ray_info(rt, &current_ray);
		pixel_color = rt_cast_ray(rt, &current_ray);
		rt->win.framebuff[i] = ft_luminosity(pixel_color.color,
		pixel_color.intensity);
	}
	return (0);
}
