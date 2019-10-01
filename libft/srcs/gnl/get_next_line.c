/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 20:44:34 by anjansse          #+#    #+#             */
/*   Updated: 2019/06/13 18:07:58 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int		save_line(int fd, char **line, char **f)
{
	int				len;
	char			*tmp;

	len = 0;
	while (f[fd][len] != '\n' && f[fd][len])
		len++;
	if (f[fd][len] == '\n')
	{
		*line = ft_strsub(f[fd], 0, len);
		*line = ft_strappend(*line, '\n');
		tmp = ft_strdup(f[fd] + len + 1);
		free(f[fd]);
		f[fd] = tmp;
		if (f[fd][0] == '\0')
			ft_strdel(&f[fd]);
	}
	else
	{
		*line = ft_strdup(f[fd]);
		ft_strdel(&f[fd]);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static char		*f[255];
	char			buff[BUFF_SIZE + 1];
	char			*tmp;
	int				fread;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((fread = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[fread] = '\0';
		if (f[fd] == NULL)
			f[fd] = ft_strnew(1);
		tmp = ft_strjoin(f[fd], buff);
		free(f[fd]);
		f[fd] = tmp;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (fread < 0)
		return (-1);
	if (fread == 0 && f[fd] == NULL)
		return (0);
	return (save_line(fd, line, f));
}
