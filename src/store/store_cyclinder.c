/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_cyclinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 11:51:33 by anjansse          #+#    #+#             */
/*   Updated: 2019/12/17 19:37:57 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		cylinder_add(t_cylinder **cylinder, t_store *storage)
{
	t_cylinder	*new_cyl;

	if (!(new_cyl = (t_cylinder*)malloc(sizeof(t_cylinder))))
		return ;
	vec_set(&(new_cyl->base), storage->vec_store_1[0],
	storage->vec_store_1[1], storage->vec_store_1[2]);
	vec_set(&(new_cyl->direction), storage->vec_store_2[0],
	storage->vec_store_2[1], storage->vec_store_2[2]);
	new_cyl->direction = vec_normalize(new_cyl->direction);
	new_cyl->radius = storage->num_store_1;
	new_cyl->height = storage->num_store_2;
	new_cyl->color = ft_rgb(storage->vec_store_3[0],
	storage->vec_store_3[1], storage->vec_store_3[2]);
	new_cyl->material = storage->num_store_3;
	*cylinder = new_cyl;
}

/*
** ----------------------------------------------------------------------------
** Cylinder storing function.
**
** {t_rt*} rt - Main structure for RT.
** {char*} info - Line containing informations about the cylinder.
** In this case, t_store is structured in the following way:
**		-> vec_store_1 = Base position of cylinder
**		-> vec_store_2 = Direction of cylinder
**		-> vec_store_3 = Color of cyclinder
**		-> num_store_1 = Radius of cylinder
**		-> num_store_2 = Height of cylinder
**		-> num_store_3 = Material of cylinder
** ----------------------------------------------------------------------------
*/

void			rt_store_cylinder(t_rt *rt, char *info)
{
	char		**infos;
	t_cylinder	*cyl;
	t_store		storage;

	infos = ft_strsplit(info, '|');
	if (ft_array_len(infos) != 6)
		send_error(ft_strdup("Error in cylinder options -- should be \
[base(x y z)] | [radius] | [height] | [color(r g b)] | [material].\n"));
	store_vector(infos[0], storage.vec_store_1);
	store_vector(infos[1], storage.vec_store_2);
	store_number(infos[2], &(storage.num_store_1));
	store_number(infos[3], &(storage.num_store_2));
	store_vector(infos[4], storage.vec_store_3);
	store_number(infos[5], &(storage.num_store_3));
	cylinder_add(&cyl, &storage);
	object_add(rt, NB_CYLINDER, (void*)cyl);
	ft_free_db_tab(infos);
}
