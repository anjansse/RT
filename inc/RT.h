#ifndef	RT_H
# define RT_H

#include "../libft/includes/libft.h"
#include <math.h>
#include <SDL.h>

/*
** Errors to send.
*/

# define ERROR_USAGE	"usage: ./RTv1 <filename>\n"

typedef struct		s_rt
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Event		e;
}					t_rt;

void				rt_game_loop(t_rt *rt);

#endif