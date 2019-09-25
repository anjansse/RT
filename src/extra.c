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
	return (pos - 2);
}