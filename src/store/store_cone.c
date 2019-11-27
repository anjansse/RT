#include "RT.h"

static void		cone_add(t_cone **cone, double cone_tips[3],
				double axis_vector[3], double half_angle, double rgb[3])
{
	t_cone	*newcone;

	if (!(newcone = (t_cone*)malloc(sizeof(t_cone))))
		return ;
	vec_set(&(newcone->cone_tips), cone_tips[0], cone_tips[1], cone_tips[2]);
	vec_set(&(newcone->axis_vector), axis_vector[0], axis_vector[1], axis_vector[2]);
	newcone->half_angle = half_angle;
	newcone->color = ft_rgb(rgb[0], rgb[1], rgb[2]);
	*cone = newcone;
}

void            rt_store_cone(t_rt *rt, char *info)
{
	double		half_angle;
	char		**infos;
	double      cone_tips[3];
	double      axis_vector[3];
	double      rgb[3];
	t_cone		*cone;

	infos = ft_strsplit(info, '|');
	if (ft_array_len(infos) != 4)
		send_error(ft_strdup("Error in sphere options -- should be \
[cone_tips(x y z)] | axis_vector(x y z) | [half_angle] | [color(r g b)].\n"));
	store_vector(infos[0], cone_tips);
	store_vector(infos[1], axis_vector);
	store_number(infos[2], &half_angle);
	store_vector(infos[3], rgb);
	cone_add(&cone, cone_tips, axis_vector, half_angle, rgb);
	object_add(rt, NB_CONE, (void*)cone);
	ft_free_db_tab(infos);
}