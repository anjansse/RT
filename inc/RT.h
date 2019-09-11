#ifndef	RT_H
# define RT_H

#include "../libft/includes/libft.h"
#include <math.h>
#include <SDL.h>

/*
** Errors to send.
*/

# define ERROR_USAGE	"usage: ./RTv1 <filename>"

typedef struct		s_rt
{
	SDL_Window		*win;
	SDL_Event		e;
	SDL_Renderer	*rend;
}					t_rt;

#endif