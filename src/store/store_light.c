/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 11:51:40 by anjansse          #+#    #+#             */
/*   Updated: 2019/12/17 19:38:04 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** ----------------------------------------------------------------------------
** Function that gets and stores the light's informations.
** Available infos are: position.
**
** @param {t_rt *} rt - Main structure for RT.
** @param {char *} infos - All the informations needed for the light.
** ----------------------------------------------------------------------------
*/

static void		light_add(t_light **light, t_store *storage)
{
	t_light		*new_light;

	if (!(new_light = (t_light*)malloc(sizeof(t_light))))
		return ;
	vec_set(&(new_light->pos), storage->vec_store_1[0],
	storage->vec_store_1[1], storage->vec_store_1[2]);
	vec_set(&(new_light->dir), storage->vec_store_2[0],
	storage->vec_store_2[1], storage->vec_store_2[2]);
	new_light->intensity = storage->num_store_1;
	*light = new_light;
	(*light)->next = NULL;
}

/*
** ----------------------------------------------------------------------------
** Light storing function.
**
** {t_rt*} rt - Main structure for RT.
** {char*} info - Line containing informations about the lights.
** In this case, t_store is structured in the following way:
**		-> vec_store_1 = Light position
**		-> vec_store_2 = Light direction
**		-> vec_store_3 = /
**		-> num_store_1 = Light intensity
**		-> num_store_2 = /
**		-> num_store_3 = /
** ----------------------------------------------------------------------------
*/

void			rt_store_light(t_rt *rt, char *info)
{
	char		**infos;
	t_light		*light;
	t_light		*current;
	t_store		storage;

	infos = ft_strsplit(info, '|');
	if (ft_array_len(infos) != 3)
		send_error(ft_strdup("Error in light options -- \
should be [position(x y z)] | [direction(xyz)] | (intensity).\n"));
	store_vector(infos[0], storage.vec_store_1);
	store_vector(infos[1], storage.vec_store_2);
	store_number(infos[2], &(storage.num_store_1));
	storage.num_store_1 = (double)(storage.num_store_1 / 100);
	light_add(&light, &storage);
	if (!rt->light)
		rt->light = light;
	else
	{
		current = rt->light;
		while (current->next)
			current = current->next;
		current->next = light;
	}
	ft_free_db_tab(infos);
}
