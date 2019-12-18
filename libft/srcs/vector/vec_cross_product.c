/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_cross_product.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 12:12:49 by anjansse          #+#    #+#             */
/*   Updated: 2019/12/17 19:00:02 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_vec		vec_cross_product(t_vec vec1, t_vec vec2)
{
	t_vec	result;

	result.x = (vec1.y * vec2.z) - (vec1.z * vec2.y);
	result.y = (vec1.z * vec2.x) - (vec1.x * vec2.z);
	result.z = (vec1.x * vec2.y) - (vec1.y * vec2.x);
	return (result);
}
