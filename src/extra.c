/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <amagnan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 12:58:29 by amagnan           #+#    #+#             */
/*   Updated: 2019/12/16 12:58:30 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

/*
** ----------------------------------------------------------------------------
** Looks in a string for the first occurance of '('.
**
** @param {char *} str - String to look at.
** @param {int} pos - Position in the string to start looking.
** ----------------------------------------------------------------------------
*/

int					find_open_p(char *str, int pos)
{
	while (pos < (int)ft_strlen(str) && str[pos] != '(')
		++pos;
	if (str[pos] != '(')
		send_error(ft_strdup("Syntax error -> (missing bracket error).\n"));
	return (pos + 1);
}

/*
** ----------------------------------------------------------------------------
** Looks in a string for the first occurance of ')'.
**
** @param {char *} str - String to look at.
** @param {int} pos - Position in the string to start looking.
** ----------------------------------------------------------------------------
*/

int					find_close_p(char *str, int pos)
{
	while (pos < (int)ft_strlen(str) && str[pos] != ')')
		++pos;
	if (str[pos] != ')')
		send_error(ft_strdup("Syntax error -> (missing bracket error).\n"));
	return (pos);
}

void				store_vector(char *info, double *xyz)
{
	char			*content;
	char			**vector;

	content = ft_strsub(info, find_open_p(info, 0),
			(find_close_p(info, 0) - find_open_p(info, 0)));
	if (!ft_verifstr(content, NUMBER))
		send_error(ft_strdup("Vectors are supposed to be numbers (x y z).\n"));
	vector = ft_strsplit(content, ' ');
	if (ft_array_len(vector) != 3)
		send_error(ft_strdup("Incorrect number of elements in vector.\n"));
	xyz[0] = (double)ft_stof(vector[0]);
	xyz[1] = (double)ft_stof(vector[1]);
	xyz[2] = (double)ft_stof(vector[2]);
	free(content);
	ft_free_db_tab(vector);
}

void				store_number(char *info, double *number)
{
	int				open_paranthese;
	int				close_paranthese;
	char			*content;

	open_paranthese = find_open_p(info, 0);
	close_paranthese = find_close_p(info, 0);
	if (open_paranthese > close_paranthese)
		send_error(ft_strjoin(info, " is invalid.\n"));
	content = ft_strsub(info, open_paranthese,
				(close_paranthese - open_paranthese));
	if (!ft_verifstr(content, NUMBER))
		send_error(ft_strdup("This is not a valid number.\n"));
	*number = (double)ft_stof(content);
	free(content);
}
