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
** @macro {ELEM} - Number of element for scene available (dispatch table)
** @macro {MIN_LINE_SIZE} - Minimum size a line should have (at least name
**							of element and a coordonate in plan).
** @macro {NUMBER} - Available characters for parsing coordonare (x y z).
** ----------------------------------------------------------------------------
*/

# define DEFAULT_BACKGROUND		rt->win.d_background

# define VEC(x,y,z) 			((t_vec){x,y,z})

# define TRUE					1
# define FALSE					0

# define NB_LIGHT				0
# define NB_SPHERE				1
# define NB_PLANE				2
# define NB_CYLINDER			3
# define NB_CONE				4

# define RAY_O					ray->ray_o
# define RAY_D					ray->ray_d
# define RAY_TYPE				ray->ray_type

# define PRIMARY_RAY			1
# define SHADOW_RAY				2
# define REFRACTION_RAY			3
# define REFLECTION_RAY			4
# define END_RAY				5

# define MAX_DEPTH  			5

# define CAM_FROM				rt->cam.pos
# define CAM_TO					rt->cam.look_at
# define CAM_MAT				rt->camMatrix

# define SPHERE					obj->sphere
# define PLANE					obj->plane
# define CYLINDER				obj->cylinder
# define CONE					obj->cone

# define FRAMEBUFF				rt->win.framebuff
# define RENDERER				rt->win.rend
# define KEYS					rt->win.keys
# define EVENT					rt->win.event
# define IMG_POINT				rt->win.img_pointer

# define ELEM					6
# define NB_OBJECTS				4
# define MIN_LINE_SIZE			11
# define NUMBER					"- 0123456789"

# define FOV					60
# define SCALE					tan(FOV * 0.5 * (M_PI / 180))	
# define WIDTH					1600
# define HEIGHT					800

# define EPSILON				0.0001

#ifndef SYSTEM_H
# include "system.h"
#endif

#ifndef OBJECTS_H
# include "objects.h"
#endif

#ifndef FUCNTIONS_H
# include "functions.h"
#endif

#include <math.h>
#include <SDL.h>
#include <SDL_thread.h>
#include "../libft/includes/libft.h"

#endif