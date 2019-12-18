/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 11:51:49 by anjansse          #+#    #+#             */
/*   Updated: 2019/12/17 19:38:13 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** ----------------------------------------------------------------------------
** The 2 functions below create a t_object element and add to it the right
** object type, and fill in the corresponding pointer of the t_object structure.
**
** @param {t_rt *} rt - Main structure for RT.
** @param {int} obj_type - flag that indicates the type of object we want
**							to create a t_object node for.
** @param {void*} obj_node - pointer to either s t_sphere or a t_light or...
**							based on the object type passed.
** ----------------------------------------------------------------------------
*/

static t_object			*create_object_elem(void)
{
	t_object *object;

	if (!(object = (t_object*)malloc(sizeof(t_object))))
		return (NULL);
	object->type = -1;
	object->sphere = NULL;
	object->plane = NULL;
	object->cylinder = NULL;
	return (object);
}

void					object_add(t_rt *rt, int obj_type, void *obj_node)
{
	t_object *object;

	if (!(object = create_object_elem()))
		return ;
	object->next = rt->obj;
	rt->obj = object;
	object->type = obj_type;
	if (obj_type == NB_SPHERE)
		object->sphere = (t_sphere*)obj_node;
	else if (obj_type == NB_PLANE)
		object->plane = (t_plane*)obj_node;
	else if (obj_type == NB_CYLINDER)
		object->cylinder = (t_cylinder*)obj_node;
	else if (obj_type == NB_CONE)
		object->cone = (t_cone*)obj_node;
}
