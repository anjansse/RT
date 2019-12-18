/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <amagnan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:27:24 by amagnan           #+#    #+#             */
/*   Updated: 2019/12/17 17:28:40 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void        free_objects(t_rt **rt)
{
	t_object	*cur;
	t_object	*n;

    cur = (*rt)->obj;
	while (cur)
	{
		n = cur->next;
		if (cur->type == NB_SPHERE)
			free(cur->sphere);
		else if (cur->type == NB_PLANE)
			free(cur->plane);
		else if (cur->type == NB_CYLINDER)
			free(cur->cylinder);
		else if (cur->type == NB_CONE)
			free(cur->cone);
		free(cur);
		cur = n;
	}
	cur = NULL;
}