/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_normalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 12:12:49 by anjansse          #+#    #+#             */
/*   Updated: 2019/10/05 11:47:55 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_vec			vec_normalize(t_vec vec)
{
	t_vec		vector;
    double      magnitude;

	vector = vec;
    magnitude = vec_magnitude(vector);
    vector.x /= magnitude;
    vector.y /= magnitude;
    vector.z /= magnitude;
	return (vector);
}
