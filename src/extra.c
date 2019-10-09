#include "RT.h"

/*
** ----------------------------------------------------------------------------
** Looks in a string for the first occurance of '('. (Can be done with strchr ? ).
**
** @param {char *} str - String to look at.
** @param {int} pos - Position in the string to start looking.
** ----------------------------------------------------------------------------
*/

int      find_open_p(char *str, int pos)
{
	while (pos < (int)ft_strlen(str) && str[pos] != '(')
		++pos;
	if (str[pos] != '(')
		send_error("Syntax error -> (missing bracket error).\n");
	return (pos + 1);
}

/*
** ----------------------------------------------------------------------------
** Looks in a string for the first occurance of ')'. (Can be done with strchr ? ).
**
** @param {char *} str - String to look at.
** @param {int} pos - Position in the string to start looking.
** ----------------------------------------------------------------------------
*/

int      find_close_p(char *str, int pos)
{
	while (pos < (int)ft_strlen(str) && str[pos] != ')')
		++pos;
	if (str[pos] != ')')
		send_error("Syntax error -> (missing bracket error).\n");
	return (pos);
}

void		store_vector(char *info, double *xyz)
{
	char		*tmp;
	char		**vector;

	tmp = ft_strsub(info, find_open_p(info, 0), (find_close_p(info, 0) - find_open_p(info, 0)));
	if (!ft_verifstr(tmp, NUMBER))
		send_error("Vectors are supposed to be numbers (x, y, z).\n");
	vector = ft_strsplit(tmp, ' ');
	if (ft_array_len(vector) != 3)
		send_error("Incorrect number of elements in vector (x y z).\n");
	xyz[0] = (double)ft_atoi(vector[0]);
	xyz[1] = (double)ft_atoi(vector[1]);
	xyz[2] = (double)ft_atoi(vector[2]);
	free(tmp);
	ft_free_db_tab(vector);
}

void		store_radius(char *info, double	*radius)
{
	char	*tmp;

	tmp = ft_strsub(info, find_open_p(info, 0), (find_close_p(info, 0) - find_open_p(info, 0)));
	if (!ft_verifstr(tmp, NUMBER))
		send_error("Radius of sphere should be a valid number.\n");
	*radius = (double)ft_atoi(tmp);
	free(tmp);
}
