#ifndef	GAME_H
# define GAME_H

/*
** ----------------------------------------------------------------------------
** Game header file, contains the object struct and window struct (used for 
** storing all the infos of the current opened window and frame buffer).
** ----------------------------------------------------------------------------
*/

#include <math.h>
#include <SDL.h>
#include "../libft/includes/libft.h"

#ifndef OBJECTS_H
# include <objects.h>
#endif

/*
** ----------------------------------------------------------------------------
** 	Window size.
**
** @macro {WIDTH} - Width of opened window.
** @macro {HEIGHT} - Height of opened window.
** ----------------------------------------------------------------------------
*/

# define WIDTH			1600
# define HEIGHT			800

/*
** ----------------------------------------------------------------------------
** Errors to send.
**
** @macro {ERROR_USAGE} - Typical usage error to send user.
** ----------------------------------------------------------------------------
*/

# define ERROR_USAGE	"usage: ./RTv1 <filename>\n"

/*
** ----------------------------------------------------------------------------
** Window structure, contains all infos for opened SDL window.
**
** @element {SDL_Window*} win - Holds all info about the Window itself.
** @element {SDL_Renderer*} rend - Keeps track the settings related to the rendering.
** @element {SDL_Texture*} img_pointer - Stores the pixel information of one element.
** @element {SDL_Event} event - Keeps track of what event has been enabled.
** @element {uint8_t} keys - Contains all the keys's informations.
** @element {uint32_t*} framebuff - Used to modify each pixels for the current frame.
** ----------------------------------------------------------------------------
*/

typedef struct			s_window
{
	SDL_Window			*win;
	SDL_Renderer		*rend;
	SDL_Texture			*img_pointer;
	SDL_Event			event;
	const uint8_t		*keys;
	uint32_t			*framebuff;
}						t_window;

/*
** ----------------------------------------------------------------------------
** Threads's structure, used to apply multithreading to the program.
**
** @element {SDL_Thread*} thread - Pointer to the correct thread's id created
**								   by SDL_CreateThread.
** @element {void*} data - Any data used by the threads (most likely qa function).
** ----------------------------------------------------------------------------
*/

typedef struct			s_thread
{
	SDL_Thread			*thread;
	void				*data;
}						t_thread;

/*
** ----------------------------------------------------------------------------
** Ray structure, used to cast ray through the projection plane and find
** intersections with the objects/light/background.
**
** @element {t_vec} ray_o - Ray's origin.
** @element {t_vec} ray_d - Ray's direction.
** ----------------------------------------------------------------------------
*/

typedef struct 			s_ray
{
	t_vec				ray_o;
	t_vec				ray_d;
}						t_ray;

/*
** ----------------------------------------------------------------------------
** Main RT's structure, contains all the important other structures.
**
** @element {t_window} win - Link to the window's structure.
** @element {t_camera} cam - Information on the camera object.
** @element {t_objects} obj - Link to the objects's structure.
** @element {t_ray} ray - Link to the ray's structure.
** @element {t_thread}  - Link to the thread's structure.
** ----------------------------------------------------------------------------
*/

typedef struct			s_rt
{
	t_window			win;
	t_camera			cam;
	t_object			*obj;
	t_ray				ray;
	t_thread			thread[4];
}						t_rt;

void				rt_game_loop(t_rt *rt);
void				rt_print_scene(t_rt *rt);
void				rt_parser(char *filename, t_rt *rt);


int         		rt_cast_ray(t_rt *rt, int pix);

int      			find_open_p(char *str, int pos);
int      			find_close_p(char *str, int pos);

#endif
