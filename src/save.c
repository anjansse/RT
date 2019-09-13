#include "RT.h"

void            save_cam_info(char *line, t_rt *rt)
{
	if (rt->par.flag & FL_CAM)
		send_error("Error: Can't have two or more cameras.\n");
	rt->par.flag |= FL_CAM;
	line = ft_strstr(line, "s(");
	// STORE INFOS BETWEEN "()""
}