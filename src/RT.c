#include "RT.h"

void			make_cam_matrix(t_rt *rt, t_vec forward, t_vec right, t_vec up)
{
	printf("%f\n", CAM_MAT[0][0] = right.x);
	printf("%f\n", CAM_MAT[0][1] = right.y);
	printf("%f\n", CAM_MAT[0][2] = right.z);
	printf("%f\n", CAM_MAT[0][3] = 0);
	printf("%f\n", CAM_MAT[1][0] = up.x);
	printf("%f\n", CAM_MAT[1][1] = up.y);
	printf("%f\n", CAM_MAT[1][2] = up.z);
	printf("%f\n", CAM_MAT[1][3] = 0);
	printf("%f\n", CAM_MAT[2][0] = forward.x);
	printf("%f\n", CAM_MAT[2][1] = forward.y);
	printf("%f\n", CAM_MAT[2][2] = forward.z);
	printf("%f\n", CAM_MAT[2][3] = 0);
	printf("%f\n", CAM_MAT[3][0] = CAM_POS.x);
	printf("%f\n", CAM_MAT[3][1] = CAM_POS.y);
	printf("%f\n", CAM_MAT[3][2] = CAM_POS.z);
	printf("%f\n", CAM_MAT[3][3] = 1);
}

static void		init_camera(t_rt *rt)
{
	t_vec	forward;
	t_vec	right;
	t_vec	up;
	
	forward = vec_normalize(vec_sub(CAM_POS, CAM_DIR));
	right = vec_cross_product(vec_new(0.0, 1.0, 0.0), forward);
	up = vec_cross_product(forward, right);
	make_cam_matrix(rt, forward, right, up);
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
        send_error(ft_strdup(ERROR_USAGE));
	rt_init_env(&rt);	
	rt_parser(av[1], &rt);
	rt_init_game(&rt);
	rt_game_loop(&rt);
	rt_quit_game(&rt);
    return (0);
}
