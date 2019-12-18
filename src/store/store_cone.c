/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 11:51:21 by anjansse          #+#    #+#             */
/*   Updated: 2019/12/17 19:37:49 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		cone_add(t_cone **cone, t_store *storage)
{
	t_cone	*newcone;

	if (!(newcone = (t_cone*)malloc(sizeof(t_cone))))
		return ;
	vec_set(&(newcone->cone_tips), storage->vec_store_1[0],
	storage->vec_store_1[1], storage->vec_store_1[2]);
	vec_set(&(newcone->axis_vector), storage->vec_store_2[0],
	storage->vec_store_2[1], storage->vec_store_2[2]);
	newcone->axis_vector = vec_normalize(newcone->axis_vector);
	newcone->half_angle = storage->num_store_1;
	newcone->color = ft_rgb(storage->vec_store_3[0],
	storage->vec_store_3[1], storage->vec_store_3[2]);
	newcone->material = storage->num_store_2;
	*cone = newcone;
}

/*
** ----------------------------------------------------------------------------
** Cone storing function.
**
** {t_rt*} rt - Main structure for RT.
** {char*} info - Line containing informations about the cone.
** In this case, t_store is structured in the following way:
**		-> vec_store_1 = cone tips
**		-> vec_store_2 = axis vector
**		-> vec_store_3 = color (rgb)
**		-> num_store_1 = cone angle
**		-> num_store_2 = cone material
**		-> num_store_3 = /
** ----------------------------------------------------------------------------
*/

void			rt_store_cone(t_rt *rt, char *info)
{
	char		**infos;
	t_store		storage;
	t_cone		*cone;

	infos = ft_strsplit(info, '|');
	if (ft_array_len(infos) != 5)
		send_error(ft_strdup("Error in sphere options -- should be \
[cone_tips(x y z)] | axis_vector(x y z) | [half_angle] | [color(r g b)].\n"));
	store_vector(infos[0], storage.vec_store_1);
	store_vector(infos[1], storage.vec_store_2);
	store_number(infos[2], &(storage.num_store_1));
	storage.num_store_1 *= (M_PI / 180);
	store_vector(infos[3], storage.vec_store_3);
	store_number(infos[4], &(storage.num_store_2));
	cone_add(&cone, &storage);
	object_add(rt, NB_CONE, (void*)cone);
	ft_free_db_tab(infos);
}
