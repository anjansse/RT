#include "RT.h"

static void		init_camera(t_rt *rt)
{
	t_vec	tmp;
	t_vec	look_at;
	
	vec_set(&look_at, 0, 5000, 0);
	vec_set(&tmp, CAM_POS.x - look_at.x, CAM_POS.y - look_at.y, CAM_POS.z - look_at.z);
	tmp = vec_scale(tmp, -1.0);
	tmp = vec_normalize(tmp);
	vec_set(&(CAM_DIR), tmp.x, tmp.y, tmp.z);
	vec_set(&tmp, 0, 1, 0);
	tmp = vec_cross_product(tmp, CAM_DIR);
	tmp = vec_normalize(tmp);
	vec_set(&(CAM_RIGHT), tmp.x, tmp.y, tmp.z);
	tmp = vec_cross_product(CAM_RIGHT, CAM_DIR);
	vec_set(&(CAM_DOWN), tmp.x, tmp.y, tmp.z);
}

/*
** ----------------------------------------------------------------------------
** Initialises the game by creating a window, a framebuffer and allocating it.
** Also initialises all the keys from local user keyboard.
** Finally, launches the game loop to keep the window open and loading the scene. 
**
** @param {t_rt *} rt - Main structure for RT.
** ----------------------------------------------------------------------------
*/

static void	rt_init_game(t_rt *rt)
{
	rt->win.win = SDL_CreateWindow("SDL_test", SDL_WINDOWPOS_UNDEFINED,\
	SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	RENDERER = SDL_CreateRenderer(rt->win.win, -1, 0);
	IMG_POINT = SDL_CreateTexture(rt->win.rend, SDL_PIXELFORMAT_ARGB8888,\
	SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	FRAMEBUFF = (uint32_t *)malloc(sizeof(uint32_t) * HEIGHT * WIDTH);
	KEYS = SDL_GetKeyboardState(NULL);
	init_camera(rt);
}

/*
** ----------------------------------------------------------------------------
** Quit's program by destroying the renderer, then the window. 
**
** @param {t_rt *} rt - Main structure for RT.
** ----------------------------------------------------------------------------
*/

static void	rt_quit_game(t_rt *rt)
{
	SDL_DestroyRenderer(RENDERER);
	SDL_DestroyWindow(rt->win.win);
	free(FRAMEBUFF);
	SDL_Quit();
}

/*
** ----------------------------------------------------------------------------
** Function that initialises all the environment variables and structs. 
**
** @param {t_rt *} rt - Main structure for RT.
** ----------------------------------------------------------------------------
*/

static void		rt_init_env(t_rt *rt)
{
	rt->obj = NULL;
}

/*
** ----------------------------------------------------------------------------
** Main function, calls all the appropriate functions that are going to run RT. 
**
** @param {int} ac - Number of elements in execution line.
** @param {char **} av - Elements contained in execution line.
** ----------------------------------------------------------------------------
*/

int         	main(int ac, char *av[])
{
	t_rt	rt;

    if (ac != 2)
        send_error(ERROR_USAGE);
	rt_init_env(&rt);	
	rt_parser(av[1], &rt);
	rt_init_game(&rt);
	rt_game_loop(&rt);
	rt_quit_game(&rt);
    return (0);
}
