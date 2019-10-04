/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_normalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 12:12:49 by anjansse          #+#    #+#             */
/*   Updated: 2019/10/03 18:47:49 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

void        vec_normalize(t_vec *vec)
{
    double      magnitude;

    magnitude = sqrt(pow(vec->x, 2) + pow(vec->y, 2) + pow(vec->z, 2));
    vec->x /= magnitude;
    vec->y /= magnitude;
    vec->z /= magnitude;
}