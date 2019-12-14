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

static void		light_add(t_light **light, double pos[3], double dir[3], double intensity)
{
	t_light		*newLight;

	if (!(newLight = (t_light*)malloc(sizeof(t_light))))
		return ;
	vec_set(&(newLight->pos), pos[0], pos[1], pos[2]);
	vec_set(&(newLight->dir), dir[0], dir[1], dir[2]);
	newLight->intensity = intensity;
	*light = newLight;
	(*light)->next = NULL;
}

// static void		light_to_world_matrix(double mat[4][4], t_vec right, t_vec up,
// 										t_vec forward, t_light *light)
// {
// 	mat[0][0] = right.x;
// 	mat[1][0] = right.y;
// 	mat[2][0] = right.z;
// 	mat[3][0] = 0;
// 	mat[0][1] = up.x;
// 	mat[1][1] = up.y;
// 	mat[2][1] = up.z;
// 	mat[3][1] = 0;
// 	mat[0][2] = forward.x;
// 	mat[1][2] = forward.y;
// 	mat[2][2] = forward.z;
// 	mat[3][2] = 0;
// 	mat[0][3] = light->pos.x;
// 	mat[1][3] = light->pos.y;
// 	mat[2][3] = light->pos.z;
// 	mat[3][3] = 1;	
// }

// static void		light_to_world_effect(t_light *light)
// {
// 	t_vec	forward;
// 	t_vec	right;
// 	t_vec	up;
// 	double	mat[4][4];

// 	forward = vec_normalize(vec_sub(light->pos, light->dir));
// 	right = vec_cross_product(vec_new(0.0, 1.0, 0.0), forward);
// 	up = vec_cross_product(forward, right);
// 	light_to_world_matrix(mat, right, up, forward, light);
// 	light->dir = vec_normalize(dir_x_mat(vec_new(0,0,-1), mat));
// 	light->pos = vec_x_mat(vec_new(0, 0, 0), mat);
	
// }

void            rt_store_light(t_rt *rt, char *info)
{
	char		**infos;
	double      pos[3];
	double      dir[3];
	double		intensity;
	t_light		*light;
	t_light		*current;

	infos = ft_strsplit(info, '|');
	if (ft_array_len(infos) != 3)
		send_error(ft_strdup("Error in light options -- \
should be [position(x y z)] | [direction(xyz)] | (intensity).\n"));
	store_vector(infos[0], pos);
	store_vector(infos[1], dir);
	store_number(infos[2], &intensity);
	intensity = (double)(intensity / 33.34);			// GHISLAIN -> T'en penses quoi ?
	light_add(&light, pos, dir, intensity);
	if (!rt->light)
		rt->light = light;
	else {
		current = rt->light;
		while (current->next) 
			current = current->next;
		current->next = light;
	}
	ft_free_db_tab(infos);
}