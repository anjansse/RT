#ifndef RT_H
# define RT_H

/*
** ----------------------------------------------------------------------------
** Main header file that calls all auxilaries structures.
** ----------------------------------------------------------------------------
*/

# define VEC(x,y,z) ((t_vec){x,y,z})

# define TRUE		1
# define FALSE		0

# define LIGHT_NB	0
# define SPHERE_NB	1
# define PLANE_NB	2

# define RAY_O      rt->ray.ray_o
# define RAY_D      rt->ray.ray_d

# define CAM_FROM   rt->cam.pos
# define CAM_MAT    rt->camMatrix
# define CAM_TO     rt->cam.look_at
# define CAM_DIR    rt->cam.dir
# define CAM_RIGHT  rt->cam.right
# define CAM_DOWN   rt->cam.down

# define SPHERE     obj->sphere

# define FRAMEBUFF  rt->win.framebuff
# define RENDERER   rt->win.rend
# define KEYS       rt->win.keys
# define EVENT      rt->win.event
# define IMG_POINT  rt->win.img_pointer

# define FOV        60
// # define SCALE      tan(FOV * 0.5 * (M_PI / 180))
# define SCALE      1

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
