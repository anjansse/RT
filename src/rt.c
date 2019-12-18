/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 13:26:47 by amagnan           #+#    #+#             */
/*   Updated: 2019/12/17 20:05:22 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			make_cam_matrix(t_rt *rt, t_vec forward, t_vec right, t_vec up)
{
	rt->cam_matrix[0][0] = right.x;
	rt->cam_matrix[1][0] = right.y;
	rt->cam_matrix[2][0] = right.z;
	rt->cam_matrix[3][0] = 0;
	rt->cam_matrix[0][1] = up.x;
	rt->cam_matrix[1][1] = up.y;
	rt->cam_matrix[2][1] = up.z;
	rt->cam_matrix[3][1] = 0;
	rt->cam_matrix[0][2] = forward.x;
	rt->cam_matrix[1][2] = forward.y;
	rt->cam_matrix[2][2] = forward.z;
	rt->cam_matrix[3][2] = 0;
	rt->cam_matrix[0][3] = rt->cam.pos.x;
	rt->cam_matrix[1][3] = rt->cam.pos.y;
	rt->cam_matrix[2][3] = rt->cam.pos.z;
	rt->cam_matrix[3][3] = 1;
}

static void		init_camera(t_rt *rt)
{
	t_vec		forward;
	t_vec		right;
	t_vec		up;

	forward = vec_normalize(vec_sub(rt->cam.pos, rt->cam.look_at));
	right = vec_cross_product(vec_new(0.0, 1.0, 0.0), forward);
	up = vec_cross_product(forward, right);
	make_cam_matrix(rt, forward, right, up);
}

/*
** ----------------------------------------------------------------------------
** Initialises the game by creating a window, a framebuffer and allocating it.
** Also initialises all the keys from local user keyboard.
** Then launches the game loop to keep the window open and loading the scene.
**
** @param {t_rt *} rt - Main structure for RT.
** ----------------------------------------------------------------------------
*/

static void		rt_init_window(t_rt *rt)
{
	rt->win.win = SDL_CreateWindow("SDL_test", SDL_WINDOWPOS_UNDEFINED,\
	SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	rt->win.rend = SDL_CreateRenderer(rt->win.win, -1, 0);
	rt->win.img_pointer = SDL_CreateTexture(rt->win.rend,
	SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	rt->win.framebuff = (uint32_t *)malloc(sizeof(uint32_t) * HEIGHT * WIDTH);
	rt->win.keys = SDL_GetKeyboardState(NULL);
	init_camera(rt);
}

/*
** ----------------------------------------------------------------------------
** Quit's program by destroying the renderer, then the window.
**
** @param {t_rt *} rt - Main structure for RT.
** ----------------------------------------------------------------------------
*/

static void		rt_quit(t_rt *rt)
{
	SDL_DestroyRenderer(rt->win.rend);
	SDL_DestroyWindow(rt->win.win);
	free(rt->win.framebuff);
	SDL_Quit();
}

/*
** ----------------------------------------------------------------------------
** Main function, calls all the appropriate functions that are going to run RT.
**
** @param {int} ac - Number of elements in execution line.
** @param {char **} av - Elements contained in execution line.
** ----------------------------------------------------------------------------
*/

int				main(int ac, char *av[])
{
	t_rt	rt;

	if (ac != 2)
		send_error(ft_strdup(ERROR_USAGE));
	rt.obj = NULL;
	rt.light = NULL;
	rt.l_mode = 5;
	rt_parser(av[1], &rt);
	rt_init_window(&rt);
	rt_main_loop(&rt);
	rt_quit(&rt);
	return (0);
}
