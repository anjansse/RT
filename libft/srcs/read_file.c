/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 15:54:05 by anjansse          #+#    #+#             */
/*   Updated: 2019/09/10 20:02:17 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int			read_file(char *filename, char **content)
{
	int				fd;
	struct stat		st;

	if (!(fd = open(filename, O_RDONLY)))
		return (0);
	*content = NULL;
	stat(filename, &st);
	if (mmap(*content, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0) == MAP_FAILED)
		return (0);
	*content = (char *)mmap(*content, st.st_size, PROT_READ, MAP_PRIVATE,\
			fd, 0);
	return (1);
}
