#include "RT.h"

void				rt_game_loop(t_rt *rt)
{
	(void)rt;
	while (1)
	{
		if (SDL_PollEvent(&rt->e))
		{
			if (SDL_QUIT == rt->e.type )
				break ;
		}
	}
}