#include "RT.h"

/*
** ----------------------------------------------------------------------------
** Dispatch table countaining ELEM number of possible elements for the scene.
** ----------------------------------------------------------------------------
*/

static t_dis                            g_dis_table[ELEM] = {
        {"C:", &rt_store_cam},
        {"L:", &rt_store_light},
        {"S:", &rt_store_sphere},
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
		send_error("Syntax error in file.\n");
	type = ft_strsub(line, 0, 2);
	while (++i < ELEM)
	{
		if (ft_strequ(type, g_dis_table[i].type))
		{
				g_dis_table[i].function(rt, &line[2]);
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

void            rt_parser(char *filename, t_rt *rt)
{
	int		i;
	int		fd;
	char	*tmp;
	char	*content;

	i = 0;
	if (ft_strlen(filename) < 3)
		send_error("Invalid file name");
	while (filename[i] != '.')
		i++;
	tmp = ft_strsub(filename, i, 4);
	if (i + 3 <= (int)ft_strlen(filename) && !ft_strcmp(tmp, ".rt"))
	{
		free(tmp);
		if ((fd = open(filename, O_RDONLY)) == -1)
			send_error("Couldn't open file.\n");
		while (get_next_line(fd, &content) > 0)
			rt_parse_line(rt, content);
		close(fd);
	}
	else
		send_error("Incorrect file.\n");
}