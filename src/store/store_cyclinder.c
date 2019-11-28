#include "RT.h"

static void		cylinder_add(t_cylinder **cylinder, double base[3], double radius, double direction[3], double height, double rgb[3])
{
	t_cylinder	*newCyl;

	if (!(newCyl = (t_cylinder*)malloc(sizeof(t_cylinder))))
		return ;
	vec_set(&(newCyl->base), base[0], base[1], base[2]);
	vec_set(&(newCyl->direction), direction[0], direction[1], direction[2]);
	newCyl->radius = radius;
	newCyl->height = height;
	newCyl->color = ft_rgb(rgb[0], rgb[1], rgb[2]);
	newCyl->material = DIFFUSE;
	*cylinder = newCyl;
}

void            rt_store_cylinder(t_rt *rt, char *info)
{
	char		**infos;
	double		radius;
	double      base[3];
	double		direction[3];
	double      rgb[3];
	double		height;
	t_cylinder	*cyl;

	infos = ft_strsplit(info, '|');
	if (ft_array_len(infos) != 5)
		send_error(ft_strdup("Error in cylinder options -- should be [base(x y z)] | [radius] | [height] | [color(r g b)].\n"));
	store_vector(infos[0], base);
	store_vector(infos[1], direction);
	store_number(infos[2], &radius);
	store_number(infos[3], &height);
	store_vector(infos[4], rgb);
	cylinder_add(&cyl, base, radius, direction, height, rgb);
	object_add(rt, NB_CYLINDER, (void*)cyl);
	ft_free_db_tab(infos);
}