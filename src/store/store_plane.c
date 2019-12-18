/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 11:51:56 by anjansse          #+#    #+#             */
/*   Updated: 2019/12/17 19:38:32 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			plane_add(t_plane **plane, t_store *storage)
{
	t_plane		*new_plane;

	if (!(new_plane = (t_plane*)malloc(sizeof(t_plane))))
		return ;
	new_plane->dist_to_origin = storage->num_store_1;
	vec_set(&(new_plane->normal), storage->vec_store_1[0],
	storage->vec_store_1[1], storage->vec_store_1[2]);
	new_plane->color = ft_rgb(storage->vec_store_2[0],
	storage->vec_store_2[1], storage->vec_store_2[2]);
	new_plane->material = storage->num_store_2;
	*plane = new_plane;
}

/*
** ----------------------------------------------------------------------------
** Plane storing function.
**
** {t_rt*} rt - Main structure for RT.
** {char*} info - Line containing informations about the plane.
** In this case, t_store is structured in the following way:
**		-> vec_store_1 = Normal of plan
**		-> vec_store_2 = Color of plan
**		-> vec_store_3 = /
**		-> num_store_1 = Plan distance to origin
**		-> num_store_2 = cone material
**		-> num_store_3 = /
** ----------------------------------------------------------------------------
*/

void				rt_store_plane(t_rt *rt, char *info)
{
	char		**infos;
	t_plane		*plane;
	t_store		storage;

	infos = ft_strsplit(info, '|');
	if (ft_array_len(infos) != 4)
		send_error(ft_strdup("Error in plane options -- should be \
[dist_to_origin] | [normal(x y z)] | [color(r g b)] | [type(type)].\n"));
	store_number(infos[0], &(storage.num_store_1));
	store_vector(infos[1], storage.vec_store_1);
	store_vector(infos[2], storage.vec_store_2);
	store_number(infos[3], &(storage.num_store_2));
	plane_add(&plane, &storage);
	plane->normal = vec_normalize(plane->normal);
	object_add(rt, NB_PLANE, (void*)plane);
	ft_free_db_tab(infos);
}
