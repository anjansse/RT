#include "RT.h"

/*
** ----------------------------------------------------------------------------
** Prints the background on the frame buffer from OriginRGB to FinalRGB.
** each rows (1 height unit) will add DeltaRGB to OriginRGB.
**
** @param {t_rt *} rt - Main structure for RT.
** ----------------------------------------------------------------------------
*/

static void			rt_store_background(t_rt *rt)
{
	double Origin_RGB[3] = {95.0, 21.0, 252.0};
	// double Final_RGB[3] = {244, 240, 255};
	double Delta_RGB[3] = {0.18625 * 2.0, 0.27375 * 2.0, 0.00375 * 2.0};
	int y;
	int x;

	y = 0;
	while (y < HEIGHT)
	{
		x = y * WIDTH;
		while (x < (y + 1) * WIDTH)
		{
			DEFAULT_BACKGROUND[x] = ft_rgb(Origin_RGB[0], Origin_RGB[1], Origin_RGB[2]);
			++x;
		}
		if (y < HEIGHT / 2)
		{
			Origin_RGB[0] += Delta_RGB[0];
			Origin_RGB[1] += Delta_RGB[1];
			Origin_RGB[2] += Delta_RGB[2];
		}
		else
		{
			Origin_RGB[0] -= Delta_RGB[0];
			Origin_RGB[1] -= Delta_RGB[1];
			Origin_RGB[2] -= Delta_RGB[2];
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
	rt_store_background(rt);
	rt_cast_rays(rt);
	SDL_UpdateTexture(IMG_POINT, NULL, FRAMEBUFF, WIDTH * sizeof (uint32_t));
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
				printf("Key Pressed\n");
				if (KEYS[SDL_SCANCODE_ESCAPE])
					exit(0);
			}
			else if (SDL_KEYUP == EVENT.type)
				printf("Key Released\n");
		}
	}
}
