/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_normalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 12:12:49 by anjansse          #+#    #+#             */
/*   Updated: 2019/10/01 16:11:29 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

void        vec_normalize(t_vec *vec)
{
    double      magnitude;

    magnitude = sqrtl(powl(vec->x, 2.0) + powl(vec->y, 2.0) + powl(vec->z, 2.0));
    vec->x /= magnitude;
    vec->y /= magnitude;
    vec->z /= magnitude;
}