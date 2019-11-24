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

static t_object	*create_object_elem(void)
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

static void		object_add(t_rt *rt, int objType, void *objNode)
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
}

/*
** ----------------------------------------------------------------------------
** Function that gets and stores the camera's informations. 
** Available infos are: position.
**
** @param {t_rt *} rt - Main structure for RT.
** @param {char *} infos - All the informations needed for the camera.
** ----------------------------------------------------------------------------
*/

void            rt_store_cam(t_rt *rt, char *info)
{
	char		**infos;
	double      xyz[3];

	infos = ft_strsplit(info, '|');
	if (ft_array_len(infos) != 2)
		send_error(ft_strjoin(info, " is invalid: Error in camera options \
-- should be [position(x y z)] | [look_at(xyz)].\n"));
	store_vector(infos[0], xyz);
	vec_set(&(CAM_FROM), xyz[0], xyz[1], xyz[2]);
	store_vector(infos[1], xyz);
	vec_set(&(CAM_TO), xyz[0], xyz[1], xyz[2]);
	ft_free_db_tab(infos);
}

/*
** ----------------------------------------------------------------------------
** Function that gets and stores the light's informations. 
** Available infos are: position.
**
** @param {t_rt *} rt - Main structure for RT.
** @param {char *} infos - All the informations needed for the light.
** ----------------------------------------------------------------------------
*/

static void		light_add(t_light **light, double pos[3], double dir[3])
{
	t_light		*newLight;

	if (!(newLight = (t_light*)malloc(sizeof(t_light))))
		return ;
	vec_set(&(newLight->pos), pos[0], pos[1], pos[2]);
	vec_set(&(newLight->dir), dir[0], dir[1], dir[2]);
	*light = newLight;
}

void            rt_store_light(t_rt *rt, char *info)
{
	char		**infos;
	double      pos[3];
	double      dir[3];
	t_light		*light;

	infos = ft_strsplit(info, '|');
	if (ft_array_len(infos) != 2)
		send_error(ft_strdup("Error in light options -- should be [position(x y z)] | [direction(xyz)].\n"));
	store_vector(infos[0], pos);
	store_vector(infos[1], dir);
	light_add(&light, pos, dir);
	object_add(rt, NB_LIGHT, (void*)light);
	ft_free_db_tab(infos);
}

/*
** ----------------------------------------------------------------------------
** Function that gets and stores the sphere's informations. 
** Available infos are: center-position, radius.
**
** @param {t_rt *} rt - Main structure for RT.
** @param {char *} infos - All the informations needed for the sphere.
** ----------------------------------------------------------------------------
*/

static void		sphere_add(t_sphere **sphere, double xyz[3], double radius, double rgb[3])
{
	t_sphere	*newSphere;

	if (!(newSphere = (t_sphere*)malloc(sizeof(t_sphere))))
		return ;
	vec_set(&(newSphere->center), xyz[0], xyz[1], xyz[2]);
	newSphere->radius = radius;
	newSphere->color = ft_rgb(rgb[0], rgb[1], rgb[2]);
	*sphere = newSphere;
}

void            rt_store_sphere(t_rt *rt, char *info)
{
	double		radius;
	char		**infos;
	double      center[3];
	double      rgb[3];
	t_sphere	*sphere;

	infos = ft_strsplit(info, '|');
	if (ft_array_len(infos) != 3)
		send_error(ft_strdup("Error in sphere options -- should be [center(x y z)] | [radius] | [color(r g b)].\n"));
	store_vector(infos[0], center);
	store_number(infos[1], &radius);
	store_vector(infos[2], rgb);
	sphere_add(&sphere, center, radius, rgb);
	object_add(rt, NB_SPHERE, (void*)sphere);
	ft_free_db_tab(infos);
}

// Change the name of the function store_radius()

static void		plane_add(t_plane **plane, double dist_to_origin, double xyz[3], double rgb[3])
{
	t_plane		*new_plane;

	if (!(new_plane = (t_plane*)malloc(sizeof(t_plane))))
		return ;
	new_plane->dist_to_origin = dist_to_origin;
	vec_set(&(new_plane->normal), xyz[0], xyz[1], xyz[2]);
	new_plane->color = ft_rgb(rgb[0], rgb[1], rgb[2]);
	*plane = new_plane;
}

// Error management regarding if the normal is (0, 0, 0)

void            rt_store_plane(t_rt *rt, char *info)
{
	double		dist_to_origin;
	char		**infos;
	double		normal[3];
	double		rgb[3];
	t_plane		*plane;

	infos = ft_strsplit(info, '|');
	if (ft_array_len(infos) != 3)
		send_error(ft_strdup("Error in plane options -- should be [dist_to_origin] | [normal(x y z)] | [color(r g b)].\n"));
	store_number(infos[0], &dist_to_origin);
	store_vector(infos[1], normal);
	store_vector(infos[2], rgb);
	plane_add(&plane, dist_to_origin, normal, rgb);
	plane->normal = vec_normalize(plane->normal);
	object_add(rt, NB_PLANE, (void*)plane);
	ft_free_db_tab(infos);
}

/*
static void		cylinder_add(t_cylinder **cylinder, double rgb[3])
{

	(void)cylinder;
	(void)rgb;
}

void            rt_store_cylinder(t_rt *rt, char *info)
{

	(void)rt;
	(void)info;
}

static void		cone_add(t_cone **cone, double rgb[3])
{

	(void)cone;
	(void)rgb;
}

void            rt_store_cone(t_rt *rt, char *info)
{

	(void)rt;
	(void)info;
}
*/
