/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:37:15 by amagnan           #+#    #+#             */
/*   Updated: 2019/12/17 20:09:34 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			rt_store_background(t_rt *rt)
{
	int i;

	i = -1;
	while (++i < WIDTH * HEIGHT)
		rt->win.d_background[i] = 0x000000;
}

/*
** ----------------------------------------------------------------------------
** Function being called by `rt_game_loop` to update everything
** to the frame buffer. (objects, background, ..)
**
** @param {t_rt *} rt - Main structure for RT.
** ----------------------------------------------------------------------------
*/

static void			rt_print(t_rt *rt)
{
	rt_store_background(rt);
	rt_render(rt);
	SDL_UpdateTexture(rt->win.img_pointer, NULL,
	rt->win.framebuff, WIDTH * sizeof(uint32_t));
	SDL_RenderClear(rt->win.rend);
	SDL_RenderCopy(rt->win.rend, rt->win.img_pointer, NULL, NULL);
	SDL_RenderPresent(rt->win.rend);
}

/*
** ----------------------------------------------------------------------------
** Main while loop of RT, display the scene once and then checks for
** events (key pressed for example).
**
** @param {t_rt *} rt - Main structure for RT.
** ----------------------------------------------------------------------------
*/

static void			loading_screen(t_rt *rt)
{
	int				i;

	i = -1;
	while (++i < (HEIGHT * WIDTH))
		rt->win.framebuff[i] = 0x000000;
	SDL_UpdateTexture(rt->win.img_pointer, NULL,
	rt->win.framebuff, WIDTH * sizeof(uint32_t));
	SDL_RenderClear(rt->win.rend);
	SDL_RenderCopy(rt->win.rend, rt->win.img_pointer, NULL, NULL);
	SDL_RenderPresent(rt->win.rend);
}

static void			handle_cmd(t_rt *rt)
{
	int				reload;

	reload = 0;
	if (rt->win.keys[SDL_SCANCODE_KP_PLUS]
	|| rt->win.keys[SDL_SCANCODE_KP_MINUS])
		rt->l_mode += rt->win.keys[SDL_SCANCODE_KP_PLUS] ? 5 : -5;
	if (rt->win.keys[SDL_SCANCODE_D] && (reload = 1) == 1)
		rt->cam_matrix[0][3] += rt->l_mode;
	else if (rt->win.keys[SDL_SCANCODE_A] && (reload = 1) == 1)
		rt->cam_matrix[0][3] -= rt->l_mode;
	else if (rt->win.keys[SDL_SCANCODE_UP] && (reload = 1) == 1)
		rt->cam_matrix[1][3] += rt->l_mode;
	else if (rt->win.keys[SDL_SCANCODE_DOWN] && (reload = 1) == 1)
		rt->cam_matrix[1][3] -= rt->l_mode;
	else if (rt->win.keys[SDL_SCANCODE_W] && (reload = 1) == 1)
		rt->cam_matrix[2][3] += rt->l_mode;
	else if (rt->win.keys[SDL_SCANCODE_S] && (reload = 1) == 1)
		rt->cam_matrix[2][3] -= rt->l_mode;
	if (reload == 1)
	{
		loading_screen(rt);
		rt_print(rt);
	}
}

void				rt_main_loop(t_rt *rt)
{
	rt_print(rt);
	while (1)
	{
		SDL_PumpEvents();
		if (SDL_PollEvent(&rt->win.event))
		{
			if (SDL_QUIT == rt->win.event.type)
				break ;
			else if (SDL_KEYDOWN == rt->win.event.type)
			{
				if (rt->win.keys[SDL_SCANCODE_ESCAPE])
					exit(0);
				handle_cmd(rt);
			}
		}
	}
}
