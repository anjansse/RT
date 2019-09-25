#ifndef OBJECTS_H
# define OBJECTS_H

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

typedef struct			s_sphere
{
	t_vec				center;
	uint32_t			radius;
	struct s_sphere		*next;
}						t_sphere;

typedef struct          s_light
{
    t_vec               pos;
    struct s_light      *next;
}                       t_light;

typedef struct			s_objects
{
	t_vec				cam;
	t_light				*light;
	t_light				*light_head;
	t_sphere			*sphere;
	t_sphere			*sphere_head;
}						t_objects;

typedef void            (t_store_disp)(t_rt*, char*);

typedef struct          s_dis {
        char            *type;
        t_store_disp    *function;
}                       t_dis;

void            rt_store_cam(t_rt *rt, char *infos);
void            rt_store_light(t_rt *rt, char *infos);
void            rt_store_sphere(t_rt *rt, char *infos);

#endif