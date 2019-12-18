/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <amagnan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:06:27 by amagnan           #+#    #+#             */
/*   Updated: 2019/12/17 19:36:05 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** ----------------------------------------------------------------------------
** Dispatch table countaining ELEM number of possible elements for the scene.
** ----------------------------------------------------------------------------
*/

static t_dis_parser		g_dis_parser_table[ELEM] = {
	{"C:", &rt_store_cam},
	{"L:", &rt_store_light},
	{"S:", &rt_store_sphere},
	{"P:", &rt_store_plane},
	{"Y:", &rt_store_cylinder},
	{"O:", &rt_store_cone},
};

/*
** ----------------------------------------------------------------------------
** Dispatching function that sorts out what element of the scene is stored in
** the current line sent by `rt_parser` function and sends the remaining
** infos to a special storing function.
**
** @param {t_rt *} rt - Main structure for RT.
** @param {char *} line - Current line in file.
** ----------------------------------------------------------------------------
*/

static void		rt_parse_line(t_rt *rt, char *line)
{
	int			i;
	char		*type;

	i = -1;
	if (ft_strlen(line) < MIN_LINE_SIZE)
		send_error(ft_strjoin(line, "\x1b[91m is invalid.\x1b[0m\n"));
	type = ft_strsub(line, 0, 2);
	while (++i < ELEM)
	{
		if (ft_strequ(type, g_dis_parser_table[i].type))
		{
			g_dis_parser_table[i].function(rt, &line[2]);
			free(type);
			return ;
		}
	}
	free(type);
}

/*
** ----------------------------------------------------------------------------
** Main parsing function, checks the files name, reads from the file if it
** could be opened and sends lines one by one to `rt_parse_line`.
**
** @param {char *} filename - Name of the file passed as argument.
** @param {t_rt *} rt - Main structure for RT.
** ----------------------------------------------------------------------------
*/

void			rt_parser(char *filename, t_rt *rt)
{
	int			fd;
	char		*content;

	if ((fd = open(filename, O_RDONLY)) == -1)
		send_error(ft_strjoin(filename,\
		"\x1b[91m couldn't be opened.\x1b[0m\n"));
	while (get_next_line(fd, &content) > 0)
		rt_parse_line(rt, content);
	close(fd);
}
