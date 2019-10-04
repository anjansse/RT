#include "RT.h"

/*
** ----------------------------------------------------------------------------
** Get's ray direction and origin. Those will be needed for all further calculs.
**
** @param {t_rt *} rt - Main structure for RT.
** @param {int} pix - Current pixel through which we will cast a ray.
** ----------------------------------------------------------------------------
*/

static void    ray_get_info(t_rt *rt, int pix)
{
   double      x;
   double      y;
   double      xa;
   double      ya;
   double      ratio;
   t_vec       product1;
   t_vec       product2;

   ratio = (double)WIDTH / (double)HEIGHT;
   x = pix % WIDTH;
   y = (pix - x) / HEIGHT;
   xa = ((x + 0.5) / WIDTH) * ratio - (((WIDTH - HEIGHT) / (double)HEIGHT) / 2);
   ya = ((HEIGHT - y) + 0.5) / HEIGHT;
   rt->ray.ray_o = rt->obj.cam.pos;
   rt->ray.ray_d = rt->ray.ray_o;
   vec_set(&product1, rt->obj.cam.right.x, rt->obj.cam.right.y, rt->obj.cam.right.z);
   vec_scale(&product1, (xa - 0.5));
   vec_set(&product2, rt->obj.cam.down.x, rt->obj.cam.down.y, rt->obj.cam.down.z);
   vec_scale(&product2, (ya - 0.5));
   vec_add(&product1, &product2);
   vec_add(&(rt->ray.ray_d), &product1);
   vec_normalize(&(rt->ray.ray_d));
   // printf("Ray direction (%f %f %f)\n", rt->ray.ray_d.x, rt->ray.ray_d.x, rt->ray.ray_d.x);
}

/*
** ----------------------------------------------------------------------------
** Thanks to ray direction and origin, this function will calculate any
** possible intersections between the primary ray and elements.
**
** @param {t_rt *} rt - Main structure for RT.
** ----------------------------------------------------------------------------
*/

static void    rt_find_intersection(t_rt *rt, int pix)
{
   double   a;
   double   b;
   double   c;
   double   disc;

   (void)pix;
   a = 1;
   b = (2 * (rt->ray.ray_o.x - rt->obj.sphere->center.x) * rt->ray.ray_d.x) +\
   (2 * (rt->ray.ray_o.y - rt->obj.sphere->center.y) * rt->ray.ray_d.y) +\
   (2 * (rt->ray.ray_o.z - rt->obj.sphere->center.z) * rt->ray.ray_d.z);
   c = pow(rt->ray.ray_o.x - rt->obj.sphere->center.x, 2) +\
   pow(rt->ray.ray_o.y - rt->obj.sphere->center.y, 2) +\
   pow(rt->ray.ray_o.z - rt->obj.sphere->center.z, 2) - (rt->obj.sphere->radius * rt->obj.sphere->radius);
   disc = b * b - 4 * a * c;
   if (disc > 0)
   {
      rt->win.framebuff[pix] = 0xFFFFFF;
   }
}

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
   ray_get_info(rt, pix);
   rt_find_intersection(rt, pix);
   return (0);
}