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

int         rt_cast_ray(t_rt *rt, int pix)
{
   int      x;
   int      y;
   double   xa;
   double   ya;
   double   ratio;
   t_vec       *scale1;
   t_vec       *scale2;

   ratio = (double)WIDTH / (double)HEIGHT;
   x = pix % WIDTH;
   y = (pix - x) / HEIGHT;
   if (WIDTH > HEIGHT)
   {
      xa = ((x + 0.5) / WIDTH) * ratio - (((WIDTH - HEIGHT) / (double)HEIGHT) / 2);
      ya = ((HEIGHT - y) + 0.5) / HEIGHT;
   }
   rt->ray.ray_o = rt->obj.cam.pos;
   rt->ray.ray_d = rt->ray.ray_o;
   /*----------------------Calculate ray direction-------------------------*/
   scale1 = &(rt->obj.cam.right);
   vec_scale(scale1, (xa - 0.5));
   scale2 = &(rt->obj.cam.down);
   vec_scale(scale2, (ya - 0.5));
   vec_add(scale1, scale2);
   vec_add(&(rt->ray.ray_d), scale1);
   /*----------------------------------------------------------------------*/
   return (0);
}