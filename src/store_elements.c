#include "RT.h"

static int      find_open_p(char *str, int pos)
{
	while (pos < (int)ft_strlen(str) && str[pos] != '(')
		pos++;
	if (str[pos] != '(')
		send_error("Syntax error -> (missing bracket error).\n");
	return (pos);
}

static int      find_close_p(char *str, int pos)
{
	while (pos < (int)ft_strlen(str) && str[pos] != ')')
		pos++;
	if (str[pos] != ')')
		send_error("Syntax error -> (missing bracket error).\n");
	return (pos);
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

void            rt_store_cam(t_rt *rt, char *infos)
{
	char		*tmp;
	char		**vector;
	double      xyz[3];

	tmp = ft_strsub(infos, find_open_p(infos, 0), find_close_p(infos, 0));
	vector = ft_strsplit(tmp, ' ');
	if (ft_array_len(vector) != 3)
		send_error("Syntax error in camera position.\n");
	xyz[0] = (double)ft_atoi(vector[0]);
	xyz[1] = (double)ft_atoi(vector[1]);
	xyz[2] = (double)ft_atoi(vector[2]);
	rt->obj.cam = vec_new(xyz[0], xyz[1], xyz[2]);
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

void            rt_store_light(t_rt *rt, char *infos)
{
	(void)rt;
	(void)infos;
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

void            rt_store_sphere(t_rt *rt, char *infos)
{
	(void)rt;
	(void)infos;
}