/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <amagnan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:01:50 by amagnan           #+#    #+#             */
/*   Updated: 2019/12/17 19:35:52 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec			vec_x_mat(t_vec v, double m[4][4])
{
	t_vec		new;
	double		w;

	new.x = v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2] + m[0][3];
	new.y = v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2] + m[1][3];
	new.z = v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2] + m[2][3];
	w = v.x * m[3][0] + v.y * m[3][1] + v.z * m[3][2] + m[3][3];
	if (w != 1 && w)
	{
		new.x /= w;
		new.y /= w;
		new.z /= w;
	}
	return (new);
}

t_vec			dir_x_mat(t_vec v, double m[4][4])
{
	t_vec		new;

	new.x = v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2];
	new.y = v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2];
	new.z = v.x * m[2][0] + v.y * m[2][1] + v.z * m[2][2];
	return (new);
}
