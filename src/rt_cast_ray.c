#include "RT.h"

/*
** ----------------------------------------------------------------------------
** Dispatch table containing ELEM nunber of possible elements, and their corresponding quadratic function.
**	We don't consider here the camera and the light elements, hence the ELEM - 2
** ----------------------------------------------------------------------------
*/

static t_dis_quad	g_dis_quad_table[ELEM - 2] = {
	{SPHERE_NB, &find_quad_equ_coefs_sphere},
};

/*
** ----------------------------------------------------------------------------
** The functions below allow to determine the coefs of the quadratic equation 
** to solve in order to find the intersection points between the object and 
** the ray at hand.
** ----------------------------------------------------------------------------
*/

void			find_quad_equ_coefs_sphere(t_rt *rt, t_object *obj, double *coefs)
{

//		printf("test FIND QUAD SPHERE\n");
		coefs[0] = vec_dot_product(RAY_D, RAY_D);
		coefs[1] = 2 * vec_dot_product(RAY_D, vec_sub(RAY_O, SPHERE->center));
		coefs[2] = vec_dot_product(vec_sub(RAY_O, SPHERE->center), \
									vec_sub(RAY_O, SPHERE->center))\
					- SPHERE->radius * SPHERE->radius;
}

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
	double	disc;
	double	q;
	double	tmp;

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
 
//	printf("QUAD TEST DISC %lf, sol1 %lf sol2 %lf\n", disc, sols[0], sols[1]);
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

bool			check_is_closest_object(double *dist, double *sols)
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

bool			intersection_object(t_rt *rt, t_object **closestObject, double *dist)
{
	t_object	*object;
	double		coefs[3];
	double		sols[2];
	int			i;

	object = rt->obj;
	while (object)
	{

//		printf("test INTERSECTION OBJECT %d\n", object->type);
		i = -1;
		// @Ghislain --> changed ELEM - 2 into something more specific
		while (++i < ELEM - 2)
			if (object->type == g_dis_quad_table[i].objType)
				g_dis_quad_table[i].function(rt, object, coefs);
		if (TRUE == solve_quadratic(coefs[0], coefs[1], coefs[2], sols))
			if (check_is_closest_object(dist, sols))
				*closestObject = object;
		object = object->next;
	}

//	printf("TEST DIST CLOSEST %lf\n", *dist);
	if (*dist > 0.0 && *dist != INFINITY)
		return (TRUE);
	return (FALSE);
}

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
	t_object	*closest_object;
	double		dist_closest_object;

	closest_object = NULL;
	dist_closest_object = INFINITY;
	if (TRUE == intersection_object(rt, &closest_object, &dist_closest_object))
	{

//		printf("TEST INTERSECTION EXISTS\n");
		FRAMEBUFF[pix] = 0xFFF0FFF0;
	}
}

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
   double	x;
   double	y;
   double	ratio;
   double	xamnt;
   double	yamnt;

   ratio = (double)WIDTH / (double)HEIGHT;
   x = (double)(pix % WIDTH);
   y = (double)(pix / WIDTH);
   xamnt = (2 * (x + 0.5) / (double)WIDTH - 1) * ratio;
   yamnt = (1 - 2 * (y + 0.5) / (double)HEIGHT);
	RAY_O = vec_x_mat(vec_new(0, 0, 0), CAM_MAT);
//	RAY_O = CAM_POS;
	RAY_D = vec_new(xamnt, yamnt, 1);
	RAY_D = vec_new(xamnt * SCALE, yamnt * SCALE, 1);
	RAY_D = vec_normalize(dir_x_mat(RAY_D, CAM_MAT));
//	printf("Ray origin: (%f, %f, %f)\n", RAY_O.x, RAY_O.y, RAY_O.z);
//	printf("Ray direction: (%f, %f, %f)\n", RAY_D.x, RAY_D.y, RAY_D.z);
}

/*
static void    ray_get_info(t_rt *rt, int pix)
{
   double      x;
   double      y;
   double      ratio;
   double		xamnt;
   double		yamnt;

   ratio = (double)WIDTH / (double)HEIGHT;
   x = (double)(pix % WIDTH);
   y = ((double)pix - x) / (double)WIDTH;
   xamnt = (2 * (x + 0.5) / (double)WIDTH - 1) * ratio;
   yamnt = (1 - 2 * (y + 0.5) / (double)HEIGHT);
   RAY_O = vec_x_mat(vec_new(0, 0, 0), CAM_MAT);
   RAY_D = vec_new(xamnt * SCALE, yamnt * SCALE, 1);
   RAY_D = vec_normalize(dir_x_mat(RAY_D, CAM_MAT));
   printf("Ray origin: (%f, %f, %f)\n", RAY_O.x, RAY_O.y, RAY_O.z);
	printf("Ray direction: (%f, %f, %f)\n", RAY_D.x, RAY_D.y, RAY_D.z);
}
*/

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
