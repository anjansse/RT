#include "RT.h"

static void	rt_init(t_rt *rt)
{
	rt->win = SDL_CreateWindow("SDL_test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_ALLOW_HIGHDPI);
	rt->rend = SDL_CreateRenderer(rt->win, -1, 0);
	SDL_SetRenderDrawColor(rt->rend, 102, 8, 202, 255);
	SDL_RenderClear(rt->rend);
	SDL_RenderPresent(rt->rend);
	rt_game_loop(rt);
}

static void	rt_quit(t_rt *rt)
{
	SDL_DestroyRenderer(rt->rend);
	SDL_DestroyWindow(rt->win);
	SDL_Quit();
}

int         main(int ac, char *av[])
{
	t_rt	rt;

	(void)av;
    if (ac != 2)
        send_error(ERROR_USAGE);
	rt_init(&rt);
	rt_quit(&rt);
    return (0);
}