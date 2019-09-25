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

typedef struct s_objects	t_objects;

/*
** ----------------------------------------------------------------------------
** Window structure, contains all infos for opened SDL window.
**
** @element {SDL_Window*} win - Holds all info about the Window itself.
** @element {SDL_Renderer*} rend - Keeps track the settings related to the rendering.
** @element {SDL_Texture*} framebuff - Stores the pixel information of one element.
** @element {SDL_Event} event - Keeps track of what event has been enabled.
** @element {uint8_t} keys - Contains all the keys's informations.
** @element {uint32_t*} pixel - Linked to the frame buffer, used to modify each
**								pixels of the allocated screen.
** ----------------------------------------------------------------------------
*/

typedef struct			s_window
{
	SDL_Window			*win;
	SDL_Renderer		*rend;
	SDL_Texture			*framebuff;
	SDL_Event			event;
	const uint8_t		*keys;
	uint32_t			*pixels;
}						t_window;

/*
** ----------------------------------------------------------------------------
** Main RT's structure, contains all the important other structures.
**
** @element {t_window} win - Link to the window's structure.
** @element {t_objects} obj - Link to the objects's structure.
** ----------------------------------------------------------------------------
*/

typedef struct			s_rt
{
	t_window			win;
	t_objects			obj;
}						t_rt;

void				rt_game_loop(t_rt *rt);
void				rt_parser(char *filename, t_rt *rt);

int      find_open_p(char *str, int pos);
int      find_close_p(char *str, int pos);

#endif