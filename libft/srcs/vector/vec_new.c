/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 12:12:34 by anjansse          #+#    #+#             */
/*   Updated: 2019/09/11 12:12:41 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_vec			vec_new(double x, double y, double z)
{
	t_vec		vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}
