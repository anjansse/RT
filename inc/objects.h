#ifndef OBJECTS_H
# define OBJECTS_H

/*
** ----------------------------------------------------------------------------
** Object header file, stores all elements's info of the scenes.
** ----------------------------------------------------------------------------
*/

#include <math.h>
#include <SDL.h>
#include "../libft/includes/libft.h"

#ifndef GAME_H
# include <game.h>
#endif

# define ELEM           3
# define MIN_LINE_SIZE  11
# define NUMBER			" 0123456789"

typedef struct s_rt     t_rt;

/*
** ----------------------------------------------------------------------------
** Sphere structure. (Linked List)
**
** @element {t_vec} center - Sphere's center location stored in a vector (x y z)
** @element {uint32_t} radius - Sphere's radius size.
** ----------------------------------------------------------------------------
*/

typedef struct			s_sphere
{
	t_vec				center;
	uint32_t			radius;
	struct s_sphere		*next;
}						t_sphere;

/*
** ----------------------------------------------------------------------------
** Light structure. (Linked List)
**
** @element {t_vec} pos - Light's location stored in a vector (x y z).
** ----------------------------------------------------------------------------
*/

typedef struct          s_light
{
    t_vec               pos;
    struct s_light      *next;
}                       t_light;

/*
** ----------------------------------------------------------------------------
** Main object's structure. Contains all elements used for RT.
**
** @element {t_vec} cam - Camera's location stored in a vector (x y z).
** @element {t_light} light - Pointer to light's structure (see above).
** @element {t_light} light_head - Head node for light's linked list.
** @element {t_sphere} sphere - Pointer to sphere's structure (see above).
** @element {t_sphere} sphere_head - Head node for sphere's linked list.
** ----------------------------------------------------------------------------
*/

typedef struct			s_objects
{
	t_vec				cam;
	t_light				*light;
	t_sphere			*sphere;
}						t_objects;

/*
** ----------------------------------------------------------------------------
** Dispatch table structure, uses lines in file given as argument to dispatch
** and store the line in the appropriate function.
**
** @comparaison {char*} type - compares known type of element with what was
**							   given as argument and sends infos to *function.
**
** @function {t_store_dis *} function - Function to send info to if type
**										comparaison matchs.
**
** @param1 {t_rt*} -  Main structure for RT.
** @param2 {char*} - Send's remaining informations to be extracted in `function`.
** ----------------------------------------------------------------------------
*/

typedef void            (t_store_disp)(t_rt*, char*);

typedef struct          s_dis {
        char            *type;
        t_store_disp    *function;
}                       t_dis;

void            rt_store_cam(t_rt *rt, char *infos);
void            rt_store_light(t_rt *rt, char *infos);
void            rt_store_sphere(t_rt *rt, char *infos);

#endif