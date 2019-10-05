#include "RT.h"

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
	char		*tmp;
	char		**vector;
	double      xyz[3];

	tmp = ft_strsub(info, find_open_p(info, 0), (find_close_p(info, 0) - find_open_p(info, 0)));
	if (!ft_verifstr(tmp, NUMBER))
		send_error("1Vectors are supposed to be numbers (x, y, z).\n");
	vector = ft_strsplit(tmp, ' ');
	if (ft_array_len(vector) != 3)
		send_error("Syntax error in camera position.\n");
	xyz[0] = (double)ft_atoi(vector[0]);
	xyz[1] = (double)ft_atoi(vector[1]);
	xyz[2] = (double)ft_atoi(vector[2]);
	vec_set(&(CAM_POS), xyz[0], xyz[1], xyz[2]);
	ft_free_db_tab(vector);
	free(tmp);
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

static void		light_add(t_light **light, double xyz[3])
{
	t_light		*newLight;

	if (!(newLight = (t_light*)malloc(sizeof(t_light))))
		return ;
	vec_set(&(newLight->pos), xyz[0], xyz[1], xyz[2]);
	newLight->next = *light;
	newLight = *light;
}

void            rt_store_light(t_rt *rt, char *info)
{
	char		*tmp;
	char		**vector;
	double      xyz[3];

	tmp = ft_strsub(info, find_open_p(info, 0), (find_close_p(info, 0) - find_open_p(info, 0)));
	if (!ft_verifstr(tmp, NUMBER))
		send_error("2Vectors are supposed to be numbers (x, y, z).\n");
	vector = ft_strsplit(tmp, ' ');
	if (ft_array_len(vector) != 3)
		send_error("Syntax error in camera position.\n");
	xyz[0] = (double)ft_atoi(vector[0]);
	xyz[1] = (double)ft_atoi(vector[1]);
	xyz[2] = (double)ft_atoi(vector[2]);
	light_add(&LIGHT, xyz);
	ft_free_db_tab(vector);
	free(tmp);
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

static void		sphere_add(t_sphere **sphere, double xyz[3], double radius)
{
	t_sphere	*newSphere;

	if (!(newSphere = (t_sphere*)malloc(sizeof(t_sphere))))
		return ;
	vec_set(&(newSphere->center), xyz[0], xyz[1], xyz[2]);
	newSphere->radius = radius;
	newSphere->color = 0x00FF00;
	newSphere->next = *sphere;
	*sphere = newSphere;
}

void            rt_store_sphere(t_rt *rt, char *info)
{
	char		*tmp;
	char		**infos;
	char		**vector;
	double      xyz[3];

	infos = ft_strsplit(info, '|');
	if (ft_array_len(infos) != 2)
		send_error("Error in sphere options -- should be [center(x y z)] | [radius].\n");
	tmp = ft_strsub(infos[0], find_open_p(infos[0], 0), (find_close_p(infos[0], 0) - find_open_p(infos[0], 0)));
	if (!ft_verifstr(tmp, NUMBER))
		send_error("3Vectors are supposed to be numbers (x, y, z).\n");
	vector = ft_strsplit(tmp, ' ');
	if (ft_array_len(vector) != 3)
		send_error("Syntax error in camera position.\n");
	xyz[0] = (double)ft_atoi(vector[0]);
	xyz[1] = (double)ft_atoi(vector[1]);
	xyz[2] = (double)ft_atoi(vector[2]);
	free(tmp);
	tmp = ft_strsub(infos[1], find_open_p(infos[1], 0), (find_close_p(infos[1], 0) - find_open_p(infos[1], 0)));
	if (!ft_verifstr(tmp, NUMBER))
		send_error("Radius of sphere should be a valid number.\n");
	sphere_add(&SPHERE, xyz, (double)ft_atoi(tmp));
	ft_free_db_tab(infos);
	ft_free_db_tab(vector);
	free(tmp);
}