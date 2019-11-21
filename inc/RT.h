#ifndef RT_H
# define RT_H

/*
** ----------------------------------------------------------------------------
** Main header file that calls all auxilaries structures.
** ----------------------------------------------------------------------------
*/

/*
** ----------------------------------------------------------------------------
** 	All macros called in RT.
**
** @macro {WIDTH} - Width of opened window.
** @macro {HEIGHT} - Height of opened window.
** ----------------------------------------------------------------------------
*/

# define DEFAULT_BACKGROUND		rt->win.d_background

# define VEC(x,y,z) 			((t_vec){x,y,z})

# define TRUE					1
# define FALSE					0

# define NB_LIGHT				0
# define NB_SPHERE				1
# define NB_PLANE				2

# define RAY_O					ray->ray_o
# define RAY_D					ray->ray_d
# define RAY_TYPE				ray->type

# define PRIMARY				1
# define LIGHT					2
# define REFRACTION				3
# define REFLECTION				4
# define END					5

# define MAX_ITERATION			5

# define CAM_FROM				rt->cam.pos
# define CAM_TO					rt->cam.look_at
# define CAM_MAT				rt->camMatrix
# define CAM_DIR				rt->cam.dir
# define CAM_RIGHT				rt->cam.right
# define CAM_DOWN				rt->cam.down

# define SPHERE					obj->sphere

# define FRAMEBUFF				rt->win.framebuff
# define RENDERER				rt->win.rend
# define KEYS					rt->win.keys
# define EVENT					rt->win.event
# define IMG_POINT				rt->win.img_pointer


# define FOV					60
# define SCALE					tan(FOV * 0.5 * (M_PI / 180))
# define WIDTH					1600
# define HEIGHT					800

#ifndef GAME_H
# include <game.h>
#endif

#ifndef OBJECTS_H
# include <objects.h>
#endif

#include <math.h>
#include <SDL.h>
#include <SDL_thread.h>
#include <stdbool.h>
// #define NK_IMPLEMENTATION
#include "../libft/includes/libft.h"

#endif
