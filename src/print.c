#include "RT.h"

// int			rt_print_1(void *data)
// {
// 	int i;
// 	t_rt *rt;

// 	i = -1;
// 	rt = ((t_rt *)data);
// 	while (++i < (WIDTH * HEIGHT / 4))
// 		rt->win.framebuff[i] = 0x00FF00;
// 	return (0);
// }

// int			rt_print_2(void *data)
// {
// 	int i;
// 	t_rt *rt;

// 	i = (WIDTH * HEIGHT / 4) -1;
// 	rt = ((t_rt *)data);
// 	while (++i < (WIDTH * HEIGHT / 4) * 2)
// 		rt->win.framebuff[i] = 0x00FF00;
// 	return (0);
// }

// int			rt_print_3(void *data)
// {
// 	int i;
// 	t_rt *rt;

// 	i = ((WIDTH * HEIGHT / 4) * 2) - 1;
// 	rt = ((t_rt *)data);
// 	while (++i < (WIDTH * HEIGHT / 4) * 3)
// 		rt->win.framebuff[i] = 0x00FF00;
// 	return (0);
// }

// int			rt_print_4(void *data)
// {
// 	int i;
// 	t_rt *rt;

// 	i = ((WIDTH * HEIGHT / 4) * 3) - 1;
// 	rt = ((t_rt *)data);
// 	while (++i < WIDTH * HEIGHT)
// 		rt->win.framebuff[i] = 0x00FF00;
// 	return (0);
// }

// void			rt_main_thread(t_rt *rt, void *fun1, void *fun2, void *fun3, void *fun4)
// {
// 	rt->thread[0].thread = SDL_CreateThread(fun1, "thread1", (void*)rt);
// 	rt->thread[1].thread = SDL_CreateThread(fun2, "thread2", (void*)rt);
// 	rt->thread[2].thread = SDL_CreateThread(fun3, "thread3", (void*)rt);
// 	rt->thread[3].thread = SDL_CreateThread(fun4, "thread4", (void*)rt);
// 	SDL_WaitThread(rt->thread[0].thread, NULL);
// 	SDL_WaitThread(rt->thread[1].thread, NULL);
// 	SDL_WaitThread(rt->thread[2].thread, NULL);
// 	SDL_WaitThread(rt->thread[3].thread, NULL);
// }

void            rt_print_scene(t_rt *rt)
{
	int		i;

	i = -1;
	while (++i < (HEIGHT * WIDTH))
		rt_check_object(rt, i);
}