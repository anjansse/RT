#include "RT.h"

static void		cylinder_add(t_cylinder **cylinder, double center[3], double radius, double height, double rgb[3])
{
	t_cylinder	*newCyl;

	if (!(newCyl = (t_cylinder*)malloc(sizeof(t_cylinder))))
		return ;
	vec_set(&(newCyl->center), center[0], center[1], center[2]);
	newCyl->height = height;
	newCyl->radius = radius;
	newCyl->color = ft_rgb(rgb[0], rgb[1], rgb[2]);
	*cylinder = newCyl;
}

void            rt_store_cylinder(t_rt *rt, char *info)
{
	double		radius;
	double		height;
	char		**infos;
	double      center[3];
	double      rgb[3];
	t_cylinder	*cyl;

	infos = ft_strsplit(info, '|');
	if (ft_array_len(infos) != 4)
		send_error(ft_strdup("Error in cylinder options -- should be [center(x y z)] | [radius] | [height] | [color(r g b)].\n"));
	store_vector(infos[0], center);
	store_number(infos[1], &radius);
	store_number(infos[2], &height);
	store_vector(infos[3], rgb);
	cylinder_add(&cyl, center, radius, height, rgb);
	object_add(rt, NB_CYLINDER, (void*)cyl);
	ft_free_db_tab(infos);
}