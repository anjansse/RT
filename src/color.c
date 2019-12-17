/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <amagnan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:23:03 by amagnan           #+#    #+#             */
/*   Updated: 2019/12/16 15:29:39 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static uint8_t			average_color(t_color reflect, t_color refract,\
						t_color scatter, int shift)
{
	double				composant;
	double				intensity;

	composant = (double)((reflect.color & (0x00ff << shift))\
	>> shift) * reflect.intensity;
	composant += (double)((refract.color & (0x00ff << shift))\
	>> shift) * refract.intensity;
	composant += (double)((scatter.color & (0x00ff << shift))\
	>> shift) * scatter.intensity;
	intensity = reflect.intensity + refract.intensity + scatter.intensity;
	return ((uint8_t)(composant / intensity));
}

uint32_t				calculate_scalar(uint32_t color, double delta_intensity)
{
	double				old_r;
	double				old_g;
	double				old_b;
	double				r;
	double				g;
	double				b;
	double				mult_intesity;

	mult_intesity = 100000 - delta_intensity * 100000;
	old_r = (color & 0xff0000) >> 16;
	old_g = (color & 0x00ff00) >> 8;
	old_b = (color & 0x0000ff);
	r = (double)(255 - old_r) / 1500;
	r = 255 - (r * mult_intesity);
	g = (double)(255 - old_g) / 1500;
	g = 255 - (g * mult_intesity);
	b = (double)(255 - old_b) / 1500;
	b = 255 - (b * mult_intesity);
	return (ft_rgb((unsigned char)r, (unsigned char)g, (unsigned char)b));
}

t_color					combine_colors(t_color reflection_color,
								t_color refraction_color,
								t_color scattering_color)
{
	t_color				color;
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;

	color.intensity = reflection_color.intensity + refraction_color.intensity\
	+ scattering_color.intensity;
	if (color.intensity == 0)
		return ((t_color){0x000000, 0});
	r = average_color(reflection_color, refraction_color, scattering_color, 16);
	g = average_color(reflection_color, refraction_color, scattering_color, 8);
	b = average_color(reflection_color, refraction_color, scattering_color, 0);
	color.color = ft_rgb((uint8_t)r, (uint8_t)g, (uint8_t)b);
	color.intensity = reflection_color.intensity + refraction_color.intensity
	+ scattering_color.intensity;
	return (color);
}

uint32_t				ft_luminosity(uint32_t color, double scale)
{
	double				r;
	double				g;
	double				b;

	r = (((color & 0xff0000) >> 16) * scale);
	if (r > 255)
		r = 255;
	g = (((color & 0x00ff00) >> 8) * scale);
	if (g > 255)
		g = 255;
	b = ((color & 0x0000ff) * scale);
	if (b > 255)
		b = 255;
	return (ft_rgb((uint8_t)r, (uint8_t)g, (uint8_t)b));
}
