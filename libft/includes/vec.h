/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 12:15:05 by anjansse          #+#    #+#             */
/*   Updated: 2019/10/05 11:38:59 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include "libft.h"

/*
** Angle to radian macro.
*/

# define ATR(a) (a * (PI / 180))

typedef struct	s_vec
{
	double		x;
	double		y;
	double		z;
}				t_vec;

t_vec			vec_new(double x, double y, double z);
t_vec			vec_add(t_vec v1, t_vec v2);
t_vec			vec_sub(t_vec v1, t_vec v2);
t_vec			vec_scale(t_vec vec, double n);
void			vec_set(t_vec *v, double x, double y, double z);
double			vec_dot_product(t_vec *v1, t_vec *v2);
double			vec_magnitude(t_vec vec);

void			vec_rotx(t_vec *vec, double angle);
void			vec_roty(t_vec *vec, double angle);
void			vec_rotz(t_vec *vec, double angle);
void			vec_rotxyz(t_vec *vec, double angle);
t_vec			vec_normalize(t_vec vec);
t_vec			vec_cross_product(t_vec *vec1, t_vec *vec2);

#endif
