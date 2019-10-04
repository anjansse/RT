#include "RT.h"

/*
** ----------------------------------------------------------------------------
** Prints the background on the frame buffer from OriginRGB to FinalRGB.
** each rows (1 height unit) will add DeltaRGB to OriginRGB.
**
** @param {t_rt *} rt - Main structure for RT.
** ----------------------------------------------------------------------------
*/

static void			rt_print_background(t_rt *rt)
{
	double Orgb[3] = {95.0, 21.0, 252.0};
	// double Frgb[3] = {244, 240, 255};
	// double Drgb[3] = {0.18625, 0.27375, 0.00375};
	double Drgb[3] = {0.18625 * 2.0, 0.27375 * 2.0, 0.00375 * 2.0};
	// double Drgb[3] = {DELTA_COLOR(Orgb[0], Frgb[0]), DELTA_COLOR(Orgb[1], Frgb[1]), DELTA_COLOR(Orgb[2], Frgb[2])};
	int y;
	int x;

	y = 0;
	while (y < HEIGHT)
	{
		x = y * WIDTH;
		while (x < (y + 1) * WIDTH)
		{
			rt->win.framebuff[x] = ft_rgb(Orgb[0], Orgb[1], Orgb[2]);
			++x;
		}
		if (y < HEIGHT / 2)
		{
			Orgb[0] += Drgb[0];
			Orgb[1] += Drgb[1];
			Orgb[2] += Drgb[2];
		}
		else
		{
			Orgb[0] -= Drgb[0];
			Orgb[1] -= Drgb[1];
			Orgb[2] -= Drgb[2];
		}
		++y;
	}
}

/*
** ----------------------------------------------------------------------------
** Function being called by `rt_game_loop` to update (clear and print) everything
** to the frame buffer. (objects, background, ..)
**
** @param {t_rt *} rt - Main structure for RT.
** ----------------------------------------------------------------------------
*/

static void			rt_print(t_rt *rt)
{
	rt_print_background(rt);
	rt_print_scene(rt);
	SDL_UpdateTexture(rt->win.img_pointer, NULL, rt->win.framebuff, WIDTH * sizeof (uint32_t));
	SDL_RenderClear(rt->win.rend);
	SDL_RenderCopy(rt->win.rend, rt->win.img_pointer, NULL, NULL);
	SDL_RenderPresent(rt->win.rend);
}

/*
** ----------------------------------------------------------------------------
** Main while loop of RT, checks for events and updates the frame buffer
** accordingly.
**
** @param {t_rt *} rt - Main structure for RT.
** ----------------------------------------------------------------------------
*/

void				rt_game_loop(t_rt *rt)
{
	while (1)
	{
		SDL_PumpEvents();
		if (SDL_PollEvent(&rt->win.event))
		{
			if (SDL_QUIT == rt->win.event.type )
				break ;
			else if (SDL_KEYDOWN == rt->win.event.type)
			{
				printf("Key Pressed\n");
				if (rt->win.keys[SDL_SCANCODE_ESCAPE])
					exit(0);
			}
			else if (SDL_KEYUP == rt->win.event.type)
				printf("Key Released\n");
			rt_print(rt);
		}
	}
}