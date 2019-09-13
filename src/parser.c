#include "RT.h"

static void		parse_line(char *line, t_rt *rt)
{
	(void)rt;
	(void)line;
// 	ft_putstr(line);
// 	if (ft_strstr(line, "camera:"))
// 		rt->par.flag |= FL_SPH;
// 		// save_cam_info(*line, rt);
// 	else if (ft_strstr(line, "sphere:"))
// 		rt->par.flag |= FL_SPH;
// 	else
// 		send_error("Error: invalid line.\n");
}

static void		parse_file(char *content, t_rt *rt)
{
	char 	**lines;

	lines = ft_strsplit(content, ';');
	while (*lines)
	{
		parse_line(*lines, rt);
		lines++;
	}
	// ft_free_db_tab(lines);
}

void            parser(char *filename, t_rt *rt)
{
	char *content;

	rt->par.flag = 0;
	read_file(filename, &content);
	parse_file(content, rt);
}