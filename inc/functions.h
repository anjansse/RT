/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 19:07:39 by anjansse          #+#    #+#             */
/*   Updated: 2019/12/22 09:18:11 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include <stdbool.h>

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
** @param2 {char*} - Send's remaining informations to be extracted
** in `function`.
** ----------------------------------------------------------------------------
*/

typedef void				(t_store_disp)(t_rt*, char*);

typedef struct				s_dis_parser
{
	char					*type;
	t_store_disp			*function;
}							t_dis_parser;

/*
** ----------------------------------------------------------------------------
** Dispatch table structure, uses object type to dispatch.
**
** @comparison {int} obj_type - compares gainst the object
** type of the object at hand.
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

typedef bool				(t_disp_intersect_fct)(t_ray*, t_object*, double*);

typedef struct				s_disp_intersection
{
	int						obj_type;
	t_disp_intersect_fct	*function;
}							t_disp_intersection;

/*
**	PARSER FUNCTIONS.
*/

void						rt_parser(char *filename, t_rt *rt);

/*
**	STORE FUNCTIONS.
*/

void						rt_store_cam(t_rt *rt, char *infos);
void						rt_store_light(t_rt *rt, char *infos);
void						rt_store_sphere(t_rt *rt, char *infos);
void						rt_store_plane(t_rt *rt, char *infos);
void						rt_store_cylinder(t_rt *rt, char *infos);
void						rt_store_cone(t_rt *rt, char *infos);
void						object_add(t_rt *rt, int obj_type, void *obj_node);

void						store_vector(char *info, double *xyz);
void						store_number(char *info, double *number);

/*
**	MAIN LOOP FUNCTIONS.
*/

void						rt_main_loop(t_rt *rt);
void						rt_print_scene(t_rt *rt);
int							rt_thread_1(void *data);
int							rt_thread_2(void *data);
int							rt_thread_3(void *data);
int							rt_thread_4(void *data);
void						rt_main_thread(t_rt *rt, void *fun1, void *fun2,
							void *fun3);
void						rt_main_thread_too(t_rt *rt, void *fun4);

/*
**	INTERSECTION FUNCTIONS.
*/

bool						find_intersection_sphere(t_ray *ray,
							t_object *object, double *object_dist);
bool						find_intersection_plane(t_ray *ray,
							t_object *object, double *object_dist);
bool						find_intersection_cone(t_ray *ray,
							t_object *object, double *object_dist);
bool						find_intersection_cylinder(t_ray *ray,
							t_object *object, double *object_dist);
bool						find_closest_intersected_object(t_rt *rt,
			t_ray *ray, t_object **closest_object, double *closest_object_dist);
bool						solve_quadratic_equa(double a, double b,
							double c, double *sols);
void						rt_ray_dispatching(t_rt *rt, t_ray *ray);

/*
**	RAY FUNCTIONS.
*/

t_color						rt_cast_ray(t_rt *rt, t_ray *ray);
void						rt_render(t_rt *rt);

void						get_primary_ray_info(t_rt *rt, t_ray *ray);
void						get_refracted_ray_infos(t_ray *ray,
		t_ray *refraction_ray, t_object *closest_object, double clos_obj_dist);
double						*get_intersection_cylinder(t_ray *ray,
							t_object *obj, double *object_dist, double *sols);

t_vec						get_normal_intersection_sphere(
							t_object *closest_object, t_vec hitpoint);
t_vec						get_normal_intersection_plane(t_ray *ray,
							t_object *closest_object);
t_vec						get_normal_intersection_cone(
							t_object *closest_object, t_vec hitpoint);
t_vec						get_normal_intersection_cylinder(
							t_object *closest_object, t_vec hitpoint);
t_vec						get_normal_at_hitpoint(t_ray *ray,
							t_object *closest_object, t_vec hitpoint);
int							check_obstructing_object_before_light(t_rt *rt,
					t_ray shadow_ray, t_light *current_light, t_vec hitpoint);

void						rt_info_refraction_ray(t_rt *rt, t_ray *ray);
void						rt_info_reflection_ray(t_rt *rt, t_ray *ray,
					t_object *closest_object, double closest_object_distance);

/*
**	COLOR FUNCTIONS
*/

uint32_t					ft_luminosity(uint32_t color, double scale);
t_color						combine_colors(t_color reflection_color,
								t_color refraction_color,
								t_color scattering_color);
t_color						get_reflected_ray_color(t_rt *rt,
							t_ray *reflection_ray, t_object *object);
uint32_t					calculate_scalar(uint32_t color,
							double delta_intensity);
t_color						get_color_object(t_color color, t_light *current_light,
				t_object *closest_object, t_vec normal, t_ray shadow_ray);

/*
**	EXTRA FUNCTIONS.
*/

int							find_open_p(char *str, int pos);
int							find_close_p(char *str, int pos);
int							check_material(t_object *closest_object,
							int material);

t_vec						vec_x_mat(t_vec v, double m[4][4]);
t_vec						dir_x_mat(t_vec v, double m[4][4]);
void						free_objects(t_rt **rt);

#endif
