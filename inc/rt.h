/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 19:07:32 by anjansse          #+#    #+#             */
/*   Updated: 2019/12/17 20:04:37 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

/*
** ----------------------------------------------------------------------------
** 	All macros called in RT.
**
** @macro {WIDTH} - Width of opened window.
** @macro {HEIGHT} - Height of opened window.
** @macro {ELEM} - Number of element for scene available (dispatch table)
** @macro {MIN_LINE_SIZE} - Minimum size a line should have (at least name
**							of element and a coordonate in plan).
** @macro {NUMBER} - Available characters for parsing coordonare (x y z).
** ----------------------------------------------------------------------------
*/

# define TRUE					1
# define FALSE					0

# define NB_SPHERE				1
# define NB_PLANE				2
# define NB_CYLINDER			3
# define NB_CONE				4

# define PRIMARY_RAY			1
# define SHADOW_RAY				2
# define REFRACTION_RAY			3
# define REFLECTION_RAY			4
# define END_RAY				5

# define DIFFUSE                1
# define REFLECTION             2
# define REFRACTION             3
# define SCALAR                 4

# define MAX_DEPTH  			5

# define ELEM					6
# define NB_OBJECTS				4
# define MIN_LINE_SIZE			11
# define NUMBER					"-. 0123456789"

# define FOV					60
# define SCALE                  1
# define WIDTH					1600
# define HEIGHT					800

# define EPSILON				0.001

# ifndef SYSTEM_H
#  include "system.h"
# endif

# ifndef OBJECTS_H
#  include "objects.h"
# endif

# ifndef FUCNTIONS_H
#  include "functions.h"
# endif

# include <math.h>
# include <SDL.h>
# include <SDL_thread.h>
# include "../libft/includes/libft.h"

#endif
