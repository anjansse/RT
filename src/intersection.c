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
   // t_vec       product1;
   // t_vec       product2;

   ratio = (double)WIDTH / (double)HEIGHT;
   x = pix % WIDTH;
   y = (pix - x) / WIDTH;
   xa = ((x + 0.5) / WIDTH) * ratio - (((WIDTH - HEIGHT) / (double)HEIGHT) / 2);
   ya = ((HEIGHT - y) + 0.5) / HEIGHT;
   RAY_O = rt->obj.cam.pos;
   // RAY_D = RAY_O;
   // vec_set(&product1, CAM_RIGHT.x, CAM_RIGHT.y, CAM_RIGHT.z);
   // product1 = vec_scale(product1, (xa - 0.5));
   // vec_set(&product2, CAM_DOWN.x, CAM_DOWN.y, CAM_DOWN.z);
   // product2 = vec_scale(product2, (ya - 0.5));
   // product1 = vec_add(product1, product2);
   // RAY_D = vec_add(RAY_D, product1);
   // RAY_D = vec_normalize(RAY_D);
   RAY_D = VEC((2 * (xa + 0.5) / (double)WIDTH - 1) * tan(60 * 0.5 * (M_PI / 180)),
			(1 - 2 * (y + 0.5) / (double)HEIGHT) * tan(60 * 0.5 * (M_PI / 180)), -1);
   // printf("pix: %d\tx: %f\ty: %f\txa: %f\tya: %f\n", pix, x, y, xa, ya);
   // printf("rd (%f %f %f)\n", RAY_D.x, RAY_D.y, RAY_D.z);
}

/*
** ----------------------------------------------------------------------------
** Thanks to ray direction and origin, this function will calculate any
** possible intersections between the primary ray and elements.
**
** @param {t_rt *} rt - Main structure for RT.
** ----------------------------------------------------------------------------
*/

static void    intersection_sphere(t_rt *rt, int pix)
{
   double   a;
   double   b;
   double   c;
   double   disc;
   t_sphere *head;

   head = rt->obj.sphere;
   while (head)
   {
      a = 1;
      b = (2 * (RAY_O.x - head->center.x) * RAY_D.x) +\
      (2 * (RAY_O.y - head->center.y) * RAY_D.y) +\
      (2 * (RAY_O.z - head->center.z) * RAY_D.z);
      c = pow(RAY_O.x - head->center.x, 2) +\
      pow(RAY_O.y - head->center.y, 2) +\
      pow(RAY_O.z - head->center.z, 2) - (head->radius * head->radius);
      disc = b * b - 4 * a * c;
      if (disc > 0)
            FRAMEBUFF[pix] = head->color;
      head = head->next;
   }
}

static void    rt_find_intersection(t_rt *rt, int pix)
{
   intersection_sphere(rt, pix);
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