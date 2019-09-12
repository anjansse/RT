#include "RT.h"

// PRINT LINEAR GRADIENT AS BACKGROUND (START FROM A COLOR TO ANOTHER COLOR BY ROWS)
// DRAW A SIMPLE CIRCLE WITH KNOWLEDGE LINKS.
// DRAW IT DEPANDING ON RAYS GIVEN
// ....

static void			rt_print_pixels(t_rt *rt)
{
	int i;

	i = 0;
	while (i < HEIGHT * WIDTH)
		rt->win.pixels[++i] = 0x00FF00;
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
			rt_print_pixels(rt);
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