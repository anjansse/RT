/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_scale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 12:13:56 by anjansse          #+#    #+#             */
/*   Updated: 2019/10/05 11:47:22 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_vec				vec_scale(t_vec vec, double n)
{
	t_vec		vector;

	vector.x = vec.x * n;
	vector.y = vec.y * n;
	vector.z = vec.z * n;
	return (vector);
}
