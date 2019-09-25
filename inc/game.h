#ifndef	GAME_H
# define GAME_H

#include <math.h>
#include <SDL.h>
#include "../libft/includes/libft.h"

#ifndef OBJECTS_H
# include <objects.h>
#endif

/*
** 	Windows options.
*/

# define WIDTH			1600
# define HEIGHT			800

/*
** Errors to send.
*/

# define ERROR_USAGE	"usage: ./RTv1 <filename>\n"

typedef struct s_objects	t_objects;

typedef struct			s_window
{
	SDL_Window			*win;
	SDL_Renderer		*rend;
	SDL_Texture			*framebuff;
	SDL_Event			e;
	const uint8_t		*keys;
	uint32_t			*pixels;
}						t_window;

typedef struct			s_rt
{
	t_window			win;
	t_objects			obj;
}						t_rt;

void				rt_game_loop(t_rt *rt);
void				rt_parser(char *filename, t_rt *rt);

void				ft_free_db_tab(char **av);

#endif