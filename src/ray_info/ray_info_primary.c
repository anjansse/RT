#include "RT.h"

void			get_primary_ray_info(t_rt *rt, t_ray *ray)
{
	int      pix_screen_x;
	int      pix_screen_y;
	double   pix_camera_x;
	double   pix_camera_y;
	double   image_ratio;
	
	pix_screen_x = (ray->pix_nb % WIDTH);
	pix_screen_y = (ray->pix_nb / WIDTH);
	image_ratio = (double)(WIDTH / HEIGHT);
	pix_camera_x = (2.0 * (pix_screen_x + 0.5) / (double)WIDTH - 1) * image_ratio * SCALE;
	pix_camera_y = (1.0 - 2.0 * (pix_screen_y + 0.5) / (double)HEIGHT) * SCALE;
	RAY_O = vec_x_mat(vec_new(0, 0, 0), CAM_MAT);
	RAY_D = dir_x_mat(vec_new(pix_camera_x, pix_camera_y, -1), CAM_MAT);
	RAY_D = vec_normalize(RAY_D);
}