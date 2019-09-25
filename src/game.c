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
	double Drgb[3] = {0.18625, 0.27375, 0.00375};
	int y;
	int x;

	y = 0;
	while (y < HEIGHT - 1)
	{
		x = y * WIDTH;
		while (x < (y + 1) * WIDTH)
		{
			rt->win.pixels[x] = ft_rgb(Orgb[0], Orgb[1], Orgb[2]);
			++x;
		}
		Orgb[0] += Drgb[0];
		Orgb[1] += Drgb[1];
		Orgb[2] += Drgb[2];
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
	SDL_UpdateTexture(rt->win.framebuff , NULL, rt->win.pixels, WIDTH * sizeof (uint32_t));
	SDL_RenderClear(rt->win.rend);
	SDL_RenderCopy(rt->win.rend, rt->win.framebuff , NULL, NULL);
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
			rt_print(rt);
			if (SDL_QUIT == rt->win.event.type )
				break ;
			else if (SDL_KEYDOWN == rt->win.event.type)
			{
				printf("Key Pressed\n");
				if (rt->win.keys[SDL_SCANCODE_ESCAPE])
					send_error("Exited\n");
			}
			else if (SDL_KEYUP == rt->win.event.type)
				printf("Key Released\n");
		}
	}
}