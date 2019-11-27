#include "RT.h"

static void		plane_add(t_plane **plane, double dist_to_origin, double xyz[3], double rgb[3])
{
	t_plane		*new_plane;

	if (!(new_plane = (t_plane*)malloc(sizeof(t_plane))))
		return ;
	new_plane->dist_to_origin = dist_to_origin;
	vec_set(&(new_plane->normal), xyz[0], xyz[1], xyz[2]);
	new_plane->color = ft_rgb(rgb[0], rgb[1], rgb[2]);
	new_plane->material = REFLECTION;
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