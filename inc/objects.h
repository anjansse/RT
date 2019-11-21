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

/*
** ----------------------------------------------------------------------------
** Some divers macros.
**
** @macro {ELEM} - Number of element for scene available (dispatch table).
** @macro {MIN_LINE_SIZE} - Minimum size a line should have (at least name
**							of element and a coordonate in plan).
** @macro {NUMBER} - Available characters for parsing coordonare (x y z).
** ----------------------------------------------------------------------------
*/

# define ELEM			3
# define MIN_LINE_SIZE	11
# define NUMBER			"- 0123456789"

typedef struct s_rt		t_rt;
typedef struct s_ray	t_ray;

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
	uint32_t			color;
	uint32_t			radius;
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
	t_vec				dir;
}                       t_light;

/*
** ----------------------------------------------------------------------------
** Camera structure.
**
** @element {t_vec} pos - Camera's location stored in a vector (x y z).
** @element {t_vec} dir - Camera's direction stored in a vector (x y z).
** @element {t_vec} right - ?? (Arnaud fill plz gracias)
** @element {t_vec} down - ?? (Arnaud fill plz gracias)
** ----------------------------------------------------------------------------
*/

typedef struct			s_camera
{
	t_vec				pos;
	t_vec				look_at;
	t_vec				down;
	t_vec				right;
	t_vec				dir;
}						t_camera;

/*
** ----------------------------------------------------------------------------
** Main object's structure. Contains all elements used for RT.
**
** @element {int} type - Contains the type of object that this node contains --> only the pointer of this type will be non-NULL
** @element {t_light} light - Pointer to light's structure (see above).
** @element {t_sphere} sphere - Pointer to sphere's structure (see above).d
** @element {t_object} next - Pointer to the next object in the sphere
** ----------------------------------------------------------------------------
*/

typedef struct			s_object
{
	int					type;
	t_light				*light;
	t_sphere			*sphere;
	struct s_object		*next;
}						t_object;

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
** @param1 {t_rt*} - Main structure for RT.
** @param2 {char*} - Send's remaining informations to be extracted in `function`.
** ----------------------------------------------------------------------------
*/

typedef void		(t_store_disp)(t_rt*, char*);

typedef struct		s_dis_parser
{
	char			*type;
	t_store_disp    *function;
}					t_dis_parser;


/*
** ----------------------------------------------------------------------------
** Dispatch table structure, uses objet type to dispatch.
**
** @comparison {int} objType - compares gainst the object type of the object at hand.
**
** @function {t_store_dis *} function - Function to send info to if type
**										comparaison matchs.
**
** @param1 {t_rt*} - Main structure for RT.
** @param2 {char*} - Send's remaining informations to be extracted in `function`.
** ----------------------------------------------------------------------------
*/

void            rt_store_cam(t_rt *rt, char *infos);
void            rt_store_light(t_rt *rt, char *infos);
void            rt_store_sphere(t_rt *rt, char *infos);

void			store_vector(char *info, double *xyz);
void			store_radius(char *info, double	*radius);

void			find_quad_equ_coefs_sphere(t_ray *ray, t_object *obj, double *coefs);

#endif
