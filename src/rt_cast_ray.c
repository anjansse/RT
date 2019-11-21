#include "RT.h"

/*
** ----------------------------------------------------------------------------
** Function used to cast the primary ray thorugh the pixel `pix` and check for any
** intersections and potential second, refraction, reflection, rays.
**
** @param {t_rt *} rt - Main structure for RT.
** @param {int} pix - Current pixel through which we will cast a ray.
** ----------------------------------------------------------------------------
*/

static void rt_get_ray_info(t_rt *rt, int pix)
{
   int      pix_screen_x;
   int      pix_screen_y;
   double   pix_camera_x;
   double   pix_camera_y;
   double   image_ratio;
   t_vec	origin;
   
   origin = vec_new(0, 0, 0);
   pix_screen_x = (pix % WIDTH);
   pix_screen_y = (pix / WIDTH);
   image_ratio = (double)(WIDTH / HEIGHT);
   pix_camera_x = (2.0 * (pix_screen_x + 0.5) / (double)WIDTH - 1) * image_ratio * SCALE;
   pix_camera_y = (1.0 - 2.0 * (pix_screen_y + 0.5) / (double)HEIGHT) * SCALE;
   RAY_O = vec_x_mat(origin, CAM_MAT);
   RAY_D = vec_x_mat(vec_new(pix_camera_x, pix_camera_y, -1), CAM_MAT);
   RAY_D = vec_normalize(RAY_D);
}

int         rt_cast_ray(t_rt *rt, int pix)
{
	rt_get_ray_info(rt, pix);
	rt_intersection(rt, pix);
	return (0);
}
