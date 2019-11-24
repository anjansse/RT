#include "RT.h"

void			rt_shade_pixel(t_rt *rt, t_ray *ray)
{
	FRAMEBUFF[ray->pix_nb] = ray->pix_color;
}

uint32_t		ft_luminosity(uint32_t color, double scale)
{
	double		r;
	double		g;
	double		b;
	r = (((color & 16711680) >> 16) * scale);
	g = (((color & 65280) >> 8) * scale);
	b = ((color & 255) * scale);
	return (ft_rgb((uint8_t)r, (uint8_t)g, (uint8_t)b));
}