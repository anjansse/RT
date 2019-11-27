#include "RT.h"

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
	newSphere->material = DIFFUSE;
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
