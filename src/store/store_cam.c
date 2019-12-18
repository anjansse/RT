/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 11:51:06 by anjansse          #+#    #+#             */
/*   Updated: 2019/12/17 19:53:06 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** ----------------------------------------------------------------------------
** Function that gets and stores the camera's informations.
** Available infos are: position.
**
** @param {t_rt *} rt - Main structure for RT.
** @param {char *} infos - All the informations needed for the camera.
** ----------------------------------------------------------------------------
*/

void			rt_store_cam(t_rt *rt, char *info)
{
	char		**infos;
	double		xyz[3];

	infos = ft_strsplit(info, '|');
	if (ft_array_len(infos) != 2)
		send_error(ft_strjoin(info, " is invalid: Error in camera options \
-- should be [position(x y z)] | [look_at(xyz)].\n"));
	store_vector(infos[0], xyz);
	vec_set(&(rt->cam.pos), xyz[0], xyz[1], xyz[2]);
	store_vector(infos[1], xyz);
	vec_set(&(rt->cam.look_at), xyz[0], xyz[1], xyz[2]);
	ft_free_db_tab(infos);
}
