/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_functions3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 07:54:32 by anjansse          #+#    #+#             */
/*   Updated: 2019/02/28 12:56:27 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

char			*append_zero(int w)
{
	int			i;
	char		*zero;

	i = 0;
	zero = (char *)ft_memalloc((sizeof(char) * w) + 1);
	while (i < w)
	{
		zero[i] = '0';
		i++;
	}
	zero[i] = '\0';
	return (zero);
}

t_answer		*apply_flag(t_answer *ret)
{
	if (ret->space == 1 && ret->plus != 1 && ret->res[0] != '-' &&
			ret->res[0] != 0 && ret->res[0] != '%' && ret->zero != '0')
		ret->res = pf_strjoinfree(" ", ret->res, ret, 1);
	if (ret->plus == 1 && ret->res[0] != '-')
		ret->res = pf_strjoinfree("+", ret->res, ret, 1);
	return (ret);
}

int				get_ps(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

char			*pf_strjoinfree(char *s1, char *s2, t_answer *ret, int t)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (ft_strcmp(ret->type, "char*") && ft_strcmp(ret->type, "percentage")
			&& (ret->res && ft_strcmp(ret->res, "")))
	{
		if (t == 0)
			ft_strdel(&s1);
		else if (t == 1)
			ft_strdel(&s2);
	}
	else if (ft_strequ(ret->type, "p"))
		ft_strdel(&s2);
	return (str);
}

char			*ft_strcpyfree(char *s1, char *s2)
{
	int		x;

	x = 0;
	while (s2[x] != '\0')
	{
		s1[x] = s2[x];
		x++;
	}
	s1[x] = '\0';
	ft_strdel(&s2);
	return (s1);
}
