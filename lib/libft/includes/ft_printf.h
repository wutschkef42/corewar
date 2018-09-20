/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <felix.wutschke@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 22:47:18 by wutschkef         #+#    #+#             */
/*   Updated: 2017/12/22 22:53:59 by wutschkef        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include "pf_defs.h"

typedef struct	s_pf_str
{
	const char	*str;
	size_t		len;
}				t_pf_str;

typedef struct	s_pf_arg
{
	size_t		len;
	size_t		pos;
	t_pf_str	str;
}				t_pf_arg;

typedef enum	e_pf_lmod
{
	NONE, H, HH, L, LL, J, Z
}				t_pf_lmod;

typedef struct	s_pf_cspec
{
	t_pf_str	str;
	int			flags;
	int			wildcard;
	int			width;
	int			prec;
	t_pf_lmod	lmod;
	char		conv;
	void		*value;
	int			cannot_parse;
}				t_pf_cspec;

typedef struct	s_pf_dispatch
{
	char		conv;
	int			(*handler)(t_pf_cspec, va_list);
}				t_pf_dispatch;

int				char_handler(t_pf_cspec cspec, va_list params);
int				string_handler(t_pf_cspec cspec, va_list params);
int				num_handler(t_pf_cspec cspec, va_list list);
int				unum_handler(t_pf_cspec cspec, va_list list);
int				escape_percent(t_pf_cspec cspec, va_list list);
int				ft_printf(const char *format, ...);
int				process_format(const char *format, va_list params);
int				seek_conv(const char *format, int *i, int *ok);
int				seek_cspec(const char *format, int *i, int *ok);
int				proceed(const char *str, size_t len, int ok, va_list params);
t_pf_cspec		init_cspec(const char *str, size_t len);
t_pf_cspec		parse_cspec(const char *str, size_t len);
int				dispatch(t_pf_cspec cspec, va_list params);
int				is_token(const char c);
int				is_wildcard(const char c);
int				is_prec(const char c);
int				is_flag(const char c);
int				is_lmod(const char c);
int				is_conv(const char c);
int				parse_flags(t_pf_cspec *cspec, const char *str, size_t *pos);
int				parse_width(t_pf_cspec *cspec, const char *str, size_t *pos);
int				parse_prec(t_pf_cspec *cspec, const char *str, size_t *pos);
int				parse_lmod(t_pf_cspec *cspec, const char *str, size_t *pos);
int				parse_conv(t_pf_cspec *cspec, const char *str, size_t *pos);
int				pf_atoi(const char *str, int *addr, size_t *i);
char			*pf_itoa2(int len, char sign, char neg, uintmax_t nabs);
char			*pf_itoa(intmax_t n, t_pf_cspec cspec, char sign);
char			*pf_uitoa_base(const char conv, uintmax_t n, size_t prec);
int				ft_putstr(const char *str, size_t len);
int				fill(const char c, size_t n);
int				print_cspec(t_pf_cspec cspec, const char *str, size_t len,
					int not_null);
void			prefix_base(t_pf_cspec cspec, int *len, char **prefix);
uintmax_t		ft_abs(intmax_t n);
size_t			ft_strlen(const char *str);
int				ft_isdigit(int c);
char			*ft_strchr(const char *str, int c);
int				ft_max(int a, int b);
size_t			numlen(intmax_t n);
size_t			unumlen(uintmax_t n, size_t base);
#endif
