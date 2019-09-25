#include "RT.h"

static void	rt_init_game(t_rt *rt)
{
	rt->win.win = SDL_CreateWindow("SDL_test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	rt->win.rend = SDL_CreateRenderer(rt->win.win, -1, 0);
	rt->win.framebuff = SDL_CreateTexture(rt->win.rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	rt->win.pixels = (uint32_t *)malloc(sizeof(uint32_t) * HEIGHT * WIDTH);
	rt->win.keys = SDL_GetKeyboardState(NULL);
	SDL_RenderClear(rt->win.rend);
	SDL_RenderPresent(rt->win.rend);
	rt_game_loop(rt);
}

static void	rt_quit_game(t_rt *rt)
{
	SDL_DestroyRenderer(rt->win.rend);
	SDL_DestroyWindow(rt->win.win);
	free(rt->win.pixels);
	SDL_Quit();
}

static void		rt_init_env(t_rt *rt)
{
	rt->obj.light = malloc(sizeof(t_light));
	rt->obj.light->next = NULL;
	rt->obj.light_head = rt->obj.light;
	rt->obj.sphere = malloc(sizeof(t_light));
	rt->obj.sphere->next = NULL;
	rt->obj.sphere_head = rt->obj.sphere;
}

int         	main(int ac, char *av[])
{
	t_rt	rt;

    if (ac != 2)
        send_error(ERROR_USAGE);
	rt_init_env(&rt);	
	rt_parser(av[1], &rt);
	rt_init_game(&rt);
	rt_quit_game(&rt);
    return (0);
}