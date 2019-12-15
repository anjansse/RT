#include "RT.h"

// /*
// ** ----------------------------------------------------------------------------
// ** Prints the background on the frame buffer from OriginRGB to FinalRGB.
// ** each rows (1 height unit) will add DeltaRGB to OriginRGB.
// **
// ** @param {t_rt *} rt - Main structure for RT.
// ** ----------------------------------------------------------------------------
// */

// static void			rt_store_background(t_rt *rt)
// {
// 	double Origin_RGB[3] = {95.0, 21.0, 252.0};
// 	// double Final_RGB[3] = {244, 240, 255};
// 	double Delta_RGB[3] = {0.18625 * 2.0, 0.27375 * 2.0, 0.00375 * 2.0};
// 	int y;
// 	int x;

// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		x = y * WIDTH;
// 		while (x < (y + 1) * WIDTH)
// 		{
// 			DEFAULT_BACKGROUND[x] = ft_rgb(Origin_RGB[0], Origin_RGB[1], Origin_RGB[2]);
// 			++x;
// 		}
// 		if (y < HEIGHT / 2)
// 		{
// 			Origin_RGB[0] += Delta_RGB[0];
// 			Origin_RGB[1] += Delta_RGB[1];
// 			Origin_RGB[2] += Delta_RGB[2];
// 		}
// 		else
// 		{
// 			Origin_RGB[0] -= Delta_RGB[0];
// 			Origin_RGB[1] -= Delta_RGB[1];
// 			Origin_RGB[2] -= Delta_RGB[2];
// 		}
// 		++y;
// 	}
// }

// /*
// ** ----------------------------------------------------------------------------
// ** Prints the background on the frame buffer from OriginRGB to FinalRGB.
// ** each rows (1 height unit) will add DeltaRGB to OriginRGB.
// **
// ** @param {t_rt *} rt - Main structure for RT.
// ** ----------------------------------------------------------------------------
// */

// static void			rt_store_background(t_rt *rt)
// {
// 	// double Origin_RGB[3] = {95.0, 21.0, 252.0};
// 	double Origin_RGB[3] = {20.0, 209.0, 255.0};
// 	// double Final_RGB[3] = {244, 240, 255};
// 	// double Delta_RGB[3] = {0.18625 * 2.0, 0.27375 * 2.0, 0.00375 * 2.0};
// 	double Delta_RGB[3] = {0.29375, 0.0575, 0.0};
// 	int y;
// 	int x;

// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		x = y * WIDTH;
// 		while (x < (y + 1) * WIDTH)
// 		{
// 			DEFAULT_BACKGROUND[x] = ft_rgb(Origin_RGB[0], Origin_RGB[1], Origin_RGB[2]);
// 			++x;
// 		}
// 		Origin_RGB[0] += Delta_RGB[0];
// 		Origin_RGB[1] += Delta_RGB[1];
// 		Origin_RGB[2] += Delta_RGB[2];
// 		++y;
// 	}
// }

/*
** ----------------------------------------------------------------------------
** Prints the background on the frame buffer from OriginRGB to FinalRGB.
** each rows (1 height unit) will add DeltaRGB to OriginRGB.
**
** @param {t_rt *} rt - Main structure for RT.
** ----------------------------------------------------------------------------
*/

// static void			rt_store_background(t_rt *rt)
// {
// 	double Origin_RGB[3] = {85.0, 85.0, 85.0};
// 	double Delta_RGB[3] = {0.2125, 0.2125, 0.2125};
// 	int y;
// 	int x;

// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		x = y * WIDTH;
// 		while (x < (y + 1) * WIDTH)
// 		{
// 			DEFAULT_BACKGROUND[x] = ft_rgb(Origin_RGB[0], Origin_RGB[1], Origin_RGB[2]);
// 			++x;
// 		}
// 		Origin_RGB[0] += Delta_RGB[0];
// 		Origin_RGB[1] += Delta_RGB[1];
// 		Origin_RGB[2] += Delta_RGB[2];
// 		++y;
// 	}
// }

static void			rt_store_background(t_rt *rt)
{
	double Origin_RGB[3] = {85.0, 85.0, 85.0};
	// double Delta_RGB[3] = {0.2125, 0.2125, 0.2125};
	double Delta_RGB[3] = {0.10625, 0.10625, 0.10625};
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
		Origin_RGB[0] -= Delta_RGB[0];
		Origin_RGB[1] -= Delta_RGB[1];
		Origin_RGB[2] -= Delta_RGB[2];
		++y;
	}
	// int x = -1;

	// while (++x < HEIGHT *WIDTH) {
	// 	DEFAULT_BACKGROUND[x] = 0x91EEFE;
	// }
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
	rt_render(rt);
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

static void			loading_screen(t_rt *rt)
{
	int i;

	i = -1;
	while (++i < (HEIGHT * WIDTH))
		FRAMEBUFF[i] = 0x000000;
	SDL_UpdateTexture(IMG_POINT, NULL, FRAMEBUFF, WIDTH * sizeof (uint32_t));
	SDL_RenderClear(RENDERER);
	SDL_RenderCopy(RENDERER, IMG_POINT, NULL, NULL);
	SDL_RenderPresent(RENDERER);
}

static void			handle_cmd(t_rt *rt)
{
	if (KEYS[SDL_SCANCODE_KP_PLUS])
		rt->LiveModeValue += 5;
	if (KEYS[SDL_SCANCODE_KP_MINUS])
		rt->LiveModeValue -= 5;
	if (LIVE_MODE == 0 && KEYS[SDL_SCANCODE_D])
	{
		CAM_MAT[0][3] += rt->LiveModeValue;
		loading_screen(rt);
		rt_print(rt);
	}
	else if (LIVE_MODE == 0 && KEYS[SDL_SCANCODE_A])
	{
		CAM_MAT[0][3] -= rt->LiveModeValue;
		loading_screen(rt);
		rt_print(rt);
	}
	else if (LIVE_MODE == 0 && KEYS[SDL_SCANCODE_W])
	{
		CAM_MAT[2][3] += rt->LiveModeValue;
		loading_screen(rt);
		rt_print(rt);
	}
	else if (LIVE_MODE == 0 && KEYS[SDL_SCANCODE_S])
	{
		CAM_MAT[2][3] -= rt->LiveModeValue;
		loading_screen(rt);
		rt_print(rt);
	}
	else if (LIVE_MODE == 0 && KEYS[SDL_SCANCODE_DOWN])
	{
		CAM_MAT[1][3] -= rt->LiveModeValue;
		loading_screen(rt);
		rt_print(rt);
	}
	else if (LIVE_MODE == 0 && KEYS[SDL_SCANCODE_UP])
	{
		CAM_MAT[1][3] += rt->LiveModeValue;
		loading_screen(rt);
		rt_print(rt);
	}
	// else if (LIVE_MODE && KEYS[SDL_SCANCODE_D])
	// {
	// 	CAM_TO.x += rt->LiveModeValue;
	// 	loading_screen(rt);
	// 	rt_print(rt);
	// }
	// else if (LIVE_MODE && KEYS[SDL_SCANCODE_A])
	// {
	// 	CAM_TO.x -= rt->LiveModeValue;
	// 	loading_screen(rt);
	// 	rt_print(rt);
	// }
	// else if (LIVE_MODE && KEYS[SDL_SCANCODE_UP])
	// {
	// 	CAM_TO.y += rt->LiveModeValue;
	// 	loading_screen(rt);
	// 	rt_print(rt);
	// }
	// else if (LIVE_MODE && KEYS[SDL_SCANCODE_DOWN])
	// {
	// 	CAM_TO.y -= rt->LiveModeValue;
	// 	loading_screen(rt);
	// 	rt_print(rt);
	// }
	// else if (LIVE_MODE && KEYS[SDL_SCANCODE_W])
	// {
	// 	CAM_TO.z += rt->LiveModeValue;
	// 	loading_screen(rt);
	// 	rt_print(rt);
	// }
	// else if (LIVE_MODE && KEYS[SDL_SCANCODE_S])
	// {
	// 	CAM_TO.z -= rt->LiveModeValue;
	// 	loading_screen(rt);
	// 	rt_print(rt);
	// }
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
				if (KEYS[SDL_SCANCODE_L])
					LIVE_MODE = (LIVE_MODE == 1) ? 0 : 1;
				handle_cmd(rt);
			}
		}
	}
}
