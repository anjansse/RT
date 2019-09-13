#include "RT.h"

/*
** Free double char array.
*/

void		ft_free_db_tab(char **av)
{
	int	i;

	i = 0;
	while (av[i] && av[i] != NULL)
		ft_strdel(&av[i++]);
	free(av);
	av = NULL;
}