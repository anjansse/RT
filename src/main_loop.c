/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:37:15 by amagnan           #+#    #+#             */
/*   Updated: 2019/12/17 15:45:07 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static void			rt_store_background(t_rt *rt)
{
	int i;

	i = -1;
	while (++i < WIDTH * HEIGHT)
		DEFAULT_BACKGROUND[i] = 0x000000;
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
	SDL_UpdateTexture(IMG_POINT, NULL, FRAMEBUFF, WIDTH * sizeof(uint32_t));
	SDL_RenderClear(RENDERER);
	SDL_RenderCopy(RENDERER, IMG_POINT, NULL, NULL);
	SDL_RenderPresent(RENDERER);
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
		FRAMEBUFF[i] = 0x000000;
	SDL_UpdateTexture(IMG_POINT, NULL, FRAMEBUFF, WIDTH * sizeof(uint32_t));
	SDL_RenderClear(RENDERER);
	SDL_RenderCopy(RENDERER, IMG_POINT, NULL, NULL);
	SDL_RenderPresent(RENDERER);
}

static void			handle_cmd(t_rt *rt)
{
	int				reload;

	reload = 0;
	if (KEYS[SDL_SCANCODE_KP_PLUS] || KEYS[SDL_SCANCODE_KP_MINUS])
		rt->LiveModeValue += KEYS[SDL_SCANCODE_KP_PLUS] ? 5 : -5;
	else
	{
		if (KEYS[SDL_SCANCODE_D] && (reload = 1) == 1)
			CAM_MAT[0][3] += rt->LiveModeValue;
		else if (KEYS[SDL_SCANCODE_A] && (reload = 1) == 1)
			CAM_MAT[0][3] -= rt->LiveModeValue;
		else if (KEYS[SDL_SCANCODE_UP] && (reload = 1) == 1)
			CAM_MAT[1][3] += rt->LiveModeValue;
		else if (KEYS[SDL_SCANCODE_DOWN] && (reload = 1) == 1)
			CAM_MAT[1][3] -= rt->LiveModeValue;
		else if (KEYS[SDL_SCANCODE_W] && (reload = 1) == 1)
			CAM_MAT[2][3] += rt->LiveModeValue;
		else if (KEYS[SDL_SCANCODE_S] && (reload = 1) == 1)
			CAM_MAT[2][3] -= rt->LiveModeValue;
		if (reload == 1)
		{
			loading_screen(rt);
			rt_print(rt);
		}
	}
}

void				rt_main_loop(t_rt *rt)
{
	rt_print(rt);
	while (1)
	{
		SDL_PumpEvents();
		if (SDL_PollEvent(&EVENT))
		{
			if (SDL_QUIT == EVENT.type)
				break ;
			else if (SDL_KEYDOWN == EVENT.type)
			{
				if (KEYS[SDL_SCANCODE_ESCAPE])
					exit(0);
				handle_cmd(rt);
			}
		}
	}
}
