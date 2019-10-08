#ifndef RT_H
# define RT_H

/*
** ----------------------------------------------------------------------------
** Main header file that calls all auxilaries structures.
** ----------------------------------------------------------------------------
*/

# define VEC(x,y,z) ((t_vec){x,y,z})

# define RAY_O      rt->ray.ray_o
# define RAY_D      rt->ray.ray_d

# define CAM_POS    rt->obj.cam.pos
# define CAM_DIR    rt->obj.cam.dir
# define CAM_RIGHT  rt->obj.cam.right
# define CAM_DOWN   rt->obj.cam.down

# define SPHERE     rt->obj.sphere
# define LIGHT      rt->obj.light

# define FRAMEBUFF  rt->win.framebuff
# define RENDERER   rt->win.rend
# define KEYS       rt->win.keys
# define EVENT      rt->win.event
# define IMG_POINT  rt->win.img_pointer

#ifndef GAME_H
# include <game.h>
#endif

#ifndef OBJECTS_H
# include <objects.h>
#endif

#include <math.h>
#include <SDL.h>
#include <SDL_thread.h>
// #define NK_IMPLEMENTATION
#include "../libft/includes/libft.h"

#endif
