/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:19:57 by anjansse          #+#    #+#             */
/*   Updated: 2019/06/13 11:25:31 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include <stddef.h>
# include <limits.h>
# include "libft.h"

typedef struct		s_arg {
	int				index;
	int				tot;
	int				flags;
	int				flags_pos[2];
	int				width;
	int				width_pos[2];
	int				prec;
	int				prec_pos[2];
	int				length;
	int				length_pos[2];
	int				specs;
	int				specs_pos[2];
}					t_arg;

typedef struct		s_answer {
	int				eos;
	char			*res;
	char			*length;
	char			*type;
	char			zero;
	char			ex;
	int				minus;
	int				plus;
	int				space;
	int				width;
	int				prec;
	int				hash;
}					t_answer;

int					ft_printf(const char *format, ...);
void				send_to_manage(int spec, char *str);
int					parse_it(t_answer *ret, t_arg *key,
		char *str, va_list list);
void				initiate_values(t_answer *ret, t_arg *key);
char				*append_zero(int width);
int					diff_w(t_answer *ret, char *str, int w);
t_arg				*create_key(t_arg *key, char *str, int beg);
t_answer			*boycott_zero(t_answer *ret);
t_answer			*apply_argument(t_answer *ret, t_arg *key, char *str,
		va_list list);
t_answer			*apply_flag(t_answer *ret);
t_answer			*add_width(t_answer *ret, t_arg *key);
t_answer			*get_width(t_answer *ret, t_arg *key, char *str,
		va_list list);

void				handle(t_answer *ret, t_arg *key, va_list list);
char				*is_hash(t_answer *ret, t_arg *key, int base, int cap);
t_answer			*minimum_dig(t_answer *ret);
t_answer			*prec_handle(t_answer *ret);

t_arg				*flags_key(t_arg *key, char *str, int beg);
t_arg				*width_key(t_arg *key, char *str, int beg);
t_arg				*prec_key(t_arg *key, char *str, int beg);
t_arg				*length_key(t_arg *key, char *str, int beg);
t_arg				*specs_key(t_arg *key, char *str, int beg);

int					check_flags(char c);
int					check_width(char c);
int					check_prec(char c);
int					check_length(char c);
int					check_specs(char c);

void				manage_d(t_answer *ret, t_arg *key, va_list list);
void				manage_s(t_answer *ret, t_arg *key, va_list list);
void				manage_c(t_answer *ret, t_arg *key, va_list list);
void				manage_u(t_answer *ret, t_arg *key, va_list list);
void				manage_ox(t_answer *ret, t_arg *key, va_list list,
		int base[2]);
void				manage_f(t_answer *ret,
		t_arg *key, va_list list, int width);
void				manage_p(t_answer *ret, t_arg *key, va_list list);
void				manage_per(t_answer *ret, t_arg *key);
t_answer			*manage_flags(t_answer *ret, t_arg *key, char *str);
t_answer			*manage_prec(t_answer *ret, t_arg *key, char *str,
		va_list list);

int					get_ps(char *str);
char				*buff_and_free(char *str);
char				*ft_cs(t_answer *ret, char c);
char				*ft_iitoa(int64_t n);
char				*ft_itoa_base(uint64_t value, int base, int cap);
char				*ft_ftoa(long double n, int width);
char				*ft_strrev(char *str, int len);
char				*pf_address(unsigned int n, t_answer *ret);
char				*pf_strjoinfree(char *s1, char *s2, t_answer *ret, int t);
char				*ft_strcpyfree(char *s1, char *s2);

#endif
