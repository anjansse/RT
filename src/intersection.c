#include "RT.h"

/*
** ----------------------------------------------------------------------------
** Solves a quadratic expression, i.e. a*x*x + b*x + c == 0.
** The function will return 1 is the equation has one or 2 solutions, \
** and 0 otherwise.
**
** @param {double*} sols will contain the solutions of the equation if they exist,
** this pointer should point to a memory area that can contain 2 floats, \
** corresponding to the 2 possible solutions.
** If there is just one solution, then the 2 memory slots will have the same value.
** ----------------------------------------------------------------------------
*/

bool			solve_quadratic(double a, double  b, double c, double *sols)
{
	float disc;
	float q;
	float tmp;

	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (FALSE);
	else if (disc == 0)
	{
		sols[0] = -0.5 * b / a;
		sols[1] = -0.5 * b / a;
	}
	else
	{
		q = (b > 0) ? -0.5 * (b + sqrt(disc)) : -0.5 * (b - sqrt(disc));
		sols[0] = q / a;
		sols[1] = c / q;
		if (sols[1] > sols[0])
		{
			tmp = sols[0];
			sols[0] = sols[1];
			sols[1] = tmp;
		}
	}
	return (TRUE);
}

/*
** ----------------------------------------------------------------------------
** Thanks to ray direction and origin, this function will calculate any
** possible intersections between the primary ray and elements.
**
** @param {t_rt *} rt - Main structure for RT.
** ----------------------------------------------------------------------------
*/

// Should we integrate some epsilon here?
// When updating the mean we do > 0, should we do >= 0

// We should return a t_sphere* with the value NULL if no sphere is intersected.
// and the address of the closest sphere otherwise.
// alternatively we should return the min distance.
// alternatively we should return a 

// CAREFUL: the ray_direction vector has to be normalized before entering 
// this function, otherwise we probably express the length the proportionnaly to 
// the vector length and not to the unit value

bool			check_closest_object(double *dist, double *sols)
{
	bool val;

	val = FALSE;
	if (sols[0] > 0 && sols[0] < *dist)
	{
		*dist = sols[0];
		val = TRUE;
	}
	if (sols[1] > 0 && sols[1] < *dist)
	{
		*dist = sols[1];
		val = TRUE;
	}
	return (val);
}

// bien de faire une fonction generique avec une structure stsnadard objet
// et d'utiliser un tableau de pointeur de fonction pour chercher l'objet le
// plus proche, ca evitera la duplication de code


/*
bool			intersection_sphere(t_rt *rt, t_sphere *closestSphere, double *dist)
{
	t_sphere	*sphere;
	double		coef[3];
	double		sols[2];

	sphere = rt->obj.sphere;
	while (sphere)
	{
		coef[0] = vec_dot_product(RAY_D, RAY_D);
		coef[1] = 2 * vec_dot_product(RAY_D, vec_sub(RAY_O, sphere->center));
		coef[2] = vec_dot_product(vec_sub(RAY_O, sphere->center), \
									vec_sub(RAY_O, sphere->center))\
					- sphere->radius * sphere->radius;
		if (TRUE == solve_quadratic(coef[0], coef[1], coef[2], sols))
			if (check_closest_object(dist, sols))
				closestSphere = sphere;
		sphere = sphere->next;
	}
	if (*dist > 0.0)
		return (TRUE);
	return (FALSE);
}
*/


// In this function, when calling the intersection functions, we could also pass
// to the functions the distance to the closest object ...



static void    rt_find_intersection(t_rt *rt, int pix)
{
	(void)rt;
	(void)pix;

/*	t_sphere	*closestSphere;
	double		distSphere;

	closestSphere = NULL;
	distSphere = -1.0;
	if (TRUE == intersection_sphere(rt, closestSphere, &distSphere))
		FRAMEBUFF[pix] = closestSphere->color;
*/}



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
   RAY_O = rt->cam.pos;
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
