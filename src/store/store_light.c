#include "RT.h"

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