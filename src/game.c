#include "RT.h"

// PRINT LINEAR GRADIENT AS BACKGROUND (START FROM A COLOR TO ANOTHER COLOR BY ROWS)
// DRAW A SIMPLE CIRCLE WITH KNOWLEDGE LINKS.
// DRAW IT DEPANDING ON RAYS GIVEN
// ....

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

static void			rt_print(t_rt *rt)
{
	rt_print_background(rt);
	// rt_print_sphere(rt);
	SDL_UpdateTexture(rt->win.framebuff , NULL, rt->win.pixels, WIDTH * sizeof (uint32_t));
	SDL_RenderClear(rt->win.rend);
	SDL_RenderCopy(rt->win.rend, rt->win.framebuff , NULL, NULL);
	SDL_RenderPresent(rt->win.rend);
}

void				rt_game_loop(t_rt *rt)
{
	while (1)
	{
		SDL_PumpEvents();
		if (SDL_PollEvent(&rt->win.e))
		{
			rt_print(rt);
			if (SDL_QUIT == rt->win.e.type )
				break ;
			else if (SDL_KEYDOWN == rt->win.e.type)
			{
				if (rt->win.keys[SDL_SCANCODE_ESCAPE]) // DISPATCH FOR KEY PRESSED
					send_error("Hello\n");
			}
			else if (SDL_KEYUP == rt->win.e.type)
				printf("oui\n");
		}
	}
}