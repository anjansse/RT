#include "RT.h"

int			rt_thread_1(void *data)
{
	int i;
    t_ray	current_ray;
	t_color	pixel_color;
	t_rt *rt;

	i = -1;
	rt = ((t_rt *)data);
	while ((current_ray.pix_nb = ++i) < (WIDTH * HEIGHT / 4)) {
		get_primary_ray_info(rt, &current_ray);
		pixel_color = rt_cast_ray(rt, &current_ray);
		FRAMEBUFF[i] = pixel_color.color;
    }
	return (0);
}

int			rt_thread_2(void *data)
{
	int i;
    t_ray	current_ray;
	t_color	pixel_color;
	t_rt *rt;

	i = (WIDTH * HEIGHT / 4) -1;
	rt = ((t_rt *)data);
	while ((current_ray.pix_nb = ++i) < (WIDTH * HEIGHT / 4) * 2) {
		get_primary_ray_info(rt, &current_ray);
		pixel_color = rt_cast_ray(rt, &current_ray);
		FRAMEBUFF[i] = pixel_color.color;
    }
	return (0);
}

int			rt_thread_3(void *data)
{
	int i;
    t_ray	current_ray;
	t_color	pixel_color;
	t_rt *rt;

	i = ((WIDTH * HEIGHT / 4) * 2) - 1;
	rt = ((t_rt *)data);
	while ((current_ray.pix_nb = ++i) < (WIDTH * HEIGHT / 4) * 3) {
		get_primary_ray_info(rt, &current_ray);
		pixel_color = rt_cast_ray(rt, &current_ray);
		FRAMEBUFF[i] = pixel_color.color;
    }
	return (0);
}

int			rt_thread_4(void *data)
{
	int i;
    t_ray	current_ray;
	t_color	pixel_color;
	t_rt *rt;

	i = ((WIDTH * HEIGHT / 4) * 3) - 1;
	rt = ((t_rt *)data);
	while ((current_ray.pix_nb = ++i) < WIDTH * HEIGHT) {
		get_primary_ray_info(rt, &current_ray);
		pixel_color = rt_cast_ray(rt, &current_ray);
		FRAMEBUFF[i] = pixel_color.color;
    }
	return (0);
}

void			rt_main_thread(t_rt *rt, void *fun1, void *fun2, void *fun3, void *fun4)
{
	rt->thread[0].thread = SDL_CreateThread(fun1, "thread1", (void*)rt);
	rt->thread[1].thread = SDL_CreateThread(fun2, "thread2", (void*)rt);
	rt->thread[2].thread = SDL_CreateThread(fun3, "thread3", (void*)rt);
	rt->thread[3].thread = SDL_CreateThread(fun4, "thread4", (void*)rt);
	SDL_WaitThread(rt->thread[0].thread, NULL);
	SDL_WaitThread(rt->thread[1].thread, NULL);
	SDL_WaitThread(rt->thread[2].thread, NULL);
	SDL_WaitThread(rt->thread[3].thread, NULL);
}

void				rt_render(t_rt *rt)
{
	rt_main_thread(rt, rt_thread_1, rt_thread_2, rt_thread_3, rt_thread_4);
}