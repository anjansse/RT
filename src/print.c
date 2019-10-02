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

/*
** ----------------------------------------------------------------------------
** Main printing function for the scene, parses all the pixels and casts rays
** through them to check for intersection with objects, and get informations
** on light, shadows and overall shade applied on the color of said object.
**
** @param {t_rt *} rt - Main structure for RT.
** ----------------------------------------------------------------------------
*/

void            rt_print_scene(t_rt *rt)
{
	t_vec	*tmp;
	int		i;

	i = -1;
	/*----------------------Calculate camera infos-------------------------*/
	tmp = &(rt->obj.cam.pos);
	vec_scale(tmp, -1.0);
	vec_normalize(tmp);
	vec_set(&(rt->obj.cam.dir), tmp->x, tmp->y, tmp->z);
	vec_set(tmp, 0, 1, 0);
	*tmp = vec_cross_product(tmp, &(rt->obj.cam.dir));
	vec_normalize(tmp);
	vec_set(&(rt->obj.cam.right), tmp->x, tmp->y, tmp->z);
	*tmp = vec_cross_product(&(rt->obj.cam.right), &(rt->obj.cam.dir));
	vec_set(&(rt->obj.cam.down), tmp->x, tmp->y, tmp->z);
	/*-------------------------------------------------------------------*/
	while (++i < (HEIGHT * WIDTH))
		rt_cast_ray(rt, i);
}