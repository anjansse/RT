/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_functions2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 15:09:36 by anjansse          #+#    #+#             */
/*   Updated: 2019/03/21 21:51:28 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int			ndig(t_answer *ret)
{
	int				len;
	int				i;

	i = 0;
	len = 0;
	while (ret->res[i])
	{
		if (ft_isalnum(ret->res[i]))
			len++;
		i++;
	}
	return ((ret->res[0] == '-' || ret->plus == 1 ||
					ret->space == 1)) ? len - 1 : len;
}

char				*is_hash(t_answer *ret, t_arg *key, int base, int cap)
{
	if (ret->hash != 1)
		return (ret->res);
	if (ft_strequ(ret->res, "") && base == 16)
		return (ret->res);
	if (ft_strequ(ret->res, "0") && key->prec == 1)
		return (ret->res = "");
	if (ft_strequ(ret->res, "0") && key->prec == 0)
		return (ret->res);
	if (base == 16 && cap == 0)
		return (ret->res = pf_strjoinfree("0x", ret->res, ret, 1));
	if (base == 16 && cap == 1)
		return (ret->res = pf_strjoinfree("0X", ret->res, ret, 1));
	if (base == 8 && cap == 0)
		return (ret->res = pf_strjoinfree("0", ret->res, ret, 1));
	if (base == 2 && cap == 0)
	{
		if (8 - (ft_strlen(ret->res) - 1) > 0)
		{
			return (ret->res = pf_strjoinfree(append_zero(8 -\
							(ft_strlen(ret->res))), ret->res, ret, 1));
		}
	}
	return (0);
}

t_answer			*minimum_dig(t_answer *ret)
{
	int				i;
	int				dig;
	char			*zero;

	i = 0;
	dig = (ret->prec >= ndig(ret) ? ret->prec - ndig(ret) : 0);
	if (dig == 0 && ft_strequ(ret->res, "0"))
		ret->res = "";
	zero = (char *)ft_memalloc(sizeof(char) * dig + 1);
	if (ret->res[0] == '-' || ret->space == 1 || ret->plus == 1)
	{
		ret = boycott_zero(ret);
		zero[i] = ret->ex;
		i++;
	}
	while (i < dig)
	{
		zero[i] = '0';
		i++;
	}
	ret->res = pf_strjoinfree(zero, ret->res, ret, 1);
	ft_strdel(&zero);
	return (ret);
}

t_answer			*prec_handle(t_answer *ret)
{
	int				i;
	char			*new_str;
	char			*old_str;

	i = 0;
	old_str = ret->res;
	new_str = (char *)ft_memalloc(sizeof(char) * ret->prec + 1);
	while (i < ret->prec)
	{
		new_str[i] = old_str[i];
		i++;
	}
	ret->res = ft_strcpyfree(ret->res, new_str);
	return (ret);
}

t_answer			*boycott_zero(t_answer *ret)
{
	char			*new_str;
	char			*old_str;
	int				i;
	int				j;

	i = 0;
	j = 1;
	if (ret->res[0] == '-')
		ret->ex = '-';
	else if (ret->res[0] != '-' && ret->space == 1)
	{
		ret->ex = ' ';
		return (ret);
	}
	else if (ret->res[0] != '-' && ret->plus == 1)
	{
		ret->ex = '+';
		return (ret);
	}
	old_str = ret->res;
	new_str = (char *)ft_memalloc(sizeof(char) * ft_strlen(old_str));
	while (old_str[j])
		new_str[i++] = old_str[j++];
	ret->res = ft_strcpyfree(ret->res, new_str);
	return (ret);
}
