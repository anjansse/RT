/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 19:07:45 by anjansse          #+#    #+#             */
/*   Updated: 2019/12/17 19:28:45 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

/*
** ----------------------------------------------------------------------------
** Object header file, stores all elements's info of the scenes.
** ----------------------------------------------------------------------------
*/

# include <math.h>
# include <SDL.h>
# include "../libft/includes/libft.h"

# ifndef SYSTEM_H
#  include "system.h"
# endif

typedef struct s_rt		t_rt;
typedef struct s_ray	t_ray;

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

typedef struct			s_store
{
	double				vec_store_1[3];
	double				vec_store_2[3];
	double				vec_store_3[3];
	double				num_store_1;
	double				num_store_2;
	double				num_store_3;
}						t_store;

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
** Light structure.
**
** @element {t_vec} pos - Light's location stored in a vector (x y z).
** ----------------------------------------------------------------------------
*/

typedef struct			s_light
{
	t_vec				pos;
	t_vec				dir;
	double				intensity;
	struct s_light		*next;
}						t_light;

/*
** ----------------------------------------------------------------------------
** Sphere structure.
**
** @element {t_vec} center - Sphere's center location stored in a vector (x y z)
** @element {uint32_t} radius - Sphere's radius size.
** ----------------------------------------------------------------------------
*/

typedef struct			s_sphere
{
	t_vec				center;
	uint32_t			radius;
	uint32_t			color;
	char				material;
}						t_sphere;

/*
** ----------------------------------------------------------------------------
** Plane structure.
** @element {double} dist_to_origin - distance of the plane to the point (0 0 0)
** @element {t_vec} normal - normal vector of the plane
** ----------------------------------------------------------------------------
*/

typedef struct			s_plane
{
	double				dist_to_origin;
	t_vec				normal;
	uint32_t			color;
	char				material;
}						t_plane;

/*
** ----------------------------------------------------------------------------
** Cylinder structure.
** ----------------------------------------------------------------------------
*/

typedef struct			s_cylinder
{
	t_vec				base;
	t_vec				direction;
	double				radius;
	double				height;
	uint32_t			color;
	char				material;
}						t_cylinder;

/*
** ----------------------------------------------------------------------------
** Cone structure.
** ----------------------------------------------------------------------------
*/

typedef struct			s_cone
{
	double				half_angle;
	t_vec				cone_tips;
	t_vec				axis_vector;
	uint32_t			color;
	char				material;
}						t_cone;

/*
** ----------------------------------------------------------------------------
** Main object's structure. Contains all elements used for RT.
**
** @element {int} type - Contains the type of object that this node contains
** --> only the pointer of this type will be non-NULL
** @element {t_light} light - Pointer to light's structure (see above).
** @element {t_sphere} sphere - Pointer to sphere's structure (see above).d
** @element {t_object} next - Pointer to the next object in the sphere
** ----------------------------------------------------------------------------
*/

typedef struct			s_object
{
	int					type;
	t_sphere			*sphere;
	t_plane				*plane;
	t_cylinder			*cylinder;
	t_cone				*cone;
	struct s_object		*next;
}						t_object;

#endif
