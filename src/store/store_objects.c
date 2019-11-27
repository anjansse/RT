#include "RT.h"

/*
** ----------------------------------------------------------------------------
** The 2 functions below create a t_object element and add to it the right object type, and fill in the corresponding pointer of the t_object structure.
**
** @param {t_rt *} rt - Main structure for RT.
** @param {int} objType - flag that indicates the type of object we want to create a t_object node for.
** @param {void*} objNode - pointer to either s t_sphere or a t_light or... based on the object type passed.
** ----------------------------------------------------------------------------
*/

static t_object			*create_object_elem(void)
{
	t_object *object;

	if (!(object = (t_object*)malloc(sizeof(t_object))))
		return (NULL);
	object->type = -1;
	object->light = NULL;
	object->sphere = NULL;
	object->plane = NULL;
	return (object);
}

void				object_add(t_rt *rt, int objType, void *objNode)
{
	t_object *object;

	if (!(object = create_object_elem()))
		return ;
	object->next = rt->obj;
	rt->obj = object;
	object->type = objType;
	if (objType == NB_LIGHT)
		object->light = (t_light*)objNode;
	else if (objType == NB_SPHERE)
		object->sphere = (t_sphere*)objNode;
	else if (objType == NB_PLANE)
		object->plane = (t_plane*)objNode;
	else if (objType == NB_CONE)
		object->cone = (t_cone*)objNode;
}