#ifndef	RT_H
# define RT_H

#include "../libft/includes/libft.h"
#include <math.h>
#include <SDL.h>

# define WIDTH			1600
# define HEIGHT			800

/*
** Errors to send.
*/

# define ERROR_USAGE	"usage: ./RTv1 <filename>\n"

typedef struct		s_window
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Texture		*framebuff;
	SDL_Event		e;
	const uint8_t	*keys;
	uint32_t		*pixels;

}					t_window;

typedef struct		s_rt
{
	t_window		win;
}					t_rt;

void				rt_game_loop(t_rt *rt);

#endif