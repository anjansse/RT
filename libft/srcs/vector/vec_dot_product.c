/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_dot_product.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 11:33:20 by anjansse          #+#    #+#             */
/*   Updated: 2019/12/17 18:58:51 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

double			vec_dot_product(t_vec v1, t_vec v2)
{
	double		result;

	result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return (result);
}
