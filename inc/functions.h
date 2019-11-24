/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:11:23 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/11/22 20:25:00 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

#include <stdbool.h>

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
** Dispatch table structure, uses object type to dispatch.
**
** @comparison {int} objType - compares gainst the object type of the object at hand.
**
** @function {disp_intersect_fct *} function - Function to send info to if type
**										comparaison matchs.
**
** @param1 {t_ray*} - Ray considered.
** @param2 {t_object*} - Object to which with which we check the intersection \
** of the ray.
** @param3 {double*} - Distance to the intersection point between the ray \
** and the object considered (if any).
** ----------------------------------------------------------------------------
*/

typedef bool			(disp_intersect_fct)(t_ray*, t_object*, double*);

typedef struct			s_disp_intersection
{
	int					objType;
	disp_intersect_fct	*function;
}						t_disp_intersection;

/*
**	PARSER FUNCTIONS.
*/

void				rt_parser(char *filename, t_rt *rt);

/*
**	STORE FUNCTIONS.
*/

void				rt_store_cam(t_rt *rt, char *infos);
void				rt_store_light(t_rt *rt, char *infos);
void				rt_store_sphere(t_rt *rt, char *infos);
void				rt_store_plane(t_rt *rt, char *infos);
void				rt_store_cylinder(t_rt *rt, char *infos);
void				rt_store_cone(t_rt *rt, char *infos);

void				store_vector(char *info, double *xyz);
void				store_number(char *info, double *number);

/*
**	MAIN LOOP FUNCTIONS.
*/

void				rt_main_loop(t_rt *rt);
void				rt_print_scene(t_rt *rt);

/*
**	INTERSECTION FUNCTIONS.
*/

bool				find_intersection_sphere(t_ray *ray, t_object *object, \
											double *object_dist);
bool				find_intersection_plane(t_ray *ray, t_object *object, \
											double *object_dist);

bool				solve_quadratic_equa(double a, double  b, double c, \
											double *sols);
void    			rt_trace_object_intersection(t_rt *rt, t_ray *ray);

/*
**	RAY FUNCTIONS.
*/

void				rt_cast_rays(t_rt *rt);

void				rt_info_primary_ray(t_rt *rt, t_ray *ray);
void				rt_info_light_ray(t_rt *rt, t_ray *ray);
void				rt_info_refraction_ray(t_rt *rt, t_ray *ray);
void				rt_info_reflection_ray(t_rt *rt, t_ray *ray);

/*
**	EXTRA FUNCTIONS.
*/

int      			find_open_p(char *str, int pos);
int      			find_close_p(char *str, int pos);

t_vec       		vec_x_mat(t_vec v, double m[4][4]);
t_vec       		dir_x_mat(t_vec v, double m[4][4]);

#endif
