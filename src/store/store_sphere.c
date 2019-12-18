/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 11:52:06 by anjansse          #+#    #+#             */
/*   Updated: 2019/12/17 19:38:28 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** ----------------------------------------------------------------------------
** Function that gets and stores the sphere's informations.
** Available infos are: center-position, radius.
**
** @param {t_rt *} rt - Main structure for RT.
** @param {char *} infos - All the informations needed for the sphere.
** ----------------------------------------------------------------------------
*/

static void		sphere_add(t_sphere **sphere, t_store *storage)
{
	t_sphere	*new_sphere;

	if (!(new_sphere = (t_sphere*)malloc(sizeof(t_sphere))))
		return ;
	vec_set(&(new_sphere->center), storage->vec_store_1[0],
	storage->vec_store_1[1], storage->vec_store_1[2]);
	new_sphere->radius = storage->num_store_1;
	new_sphere->color = ft_rgb(storage->vec_store_2[0],
	storage->vec_store_2[1], storage->vec_store_2[2]);
	new_sphere->material = storage->num_store_2;
	*sphere = new_sphere;
}

/*
** ----------------------------------------------------------------------------
** Sphere storing function.
**
** {t_rt*} rt - Main structure for RT.
** {char*} info - Line containing informations about the sphere.
** In this case, t_store is structured in the following way:
**		-> vec_store_1 = sphere center
**		-> vec_store_2 = sphere color
**		-> vec_store_3 = /
**		-> num_store_1 = sphere radius
**		-> num_store_2 = sphere material
**		-> num_store_3 = /
** ----------------------------------------------------------------------------
*/

void			rt_store_sphere(t_rt *rt, char *info)
{
	char		**infos;
	t_sphere	*sphere;
	t_store		storage;

	infos = ft_strsplit(info, '|');
	if (ft_array_len(infos) != 4)
		send_error(ft_strdup("Error in sphere options -- should be \
[center(x y z)] | [radius] | [color(r g b)] | [type(type)].\n"));
	store_vector(infos[0], storage.vec_store_1);
	store_number(infos[1], &(storage.num_store_1));
	store_vector(infos[2], storage.vec_store_2);
	store_number(infos[3], &(storage.num_store_2));
	sphere_add(&sphere, &storage);
	object_add(rt, NB_SPHERE, (void*)sphere);
	ft_free_db_tab(infos);
}
