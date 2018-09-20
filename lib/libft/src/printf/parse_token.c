/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <felix.wutschke@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 19:52:17 by wutschkef         #+#    #+#             */
/*   Updated: 2017/12/30 09:58:57 by wutschkef        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		parse_flags(t_pf_cspec *cspec, const char *str, size_t *pos)
{
	size_t	i;

	i = *pos;
	while (i < cspec->str.len - 1)
	{
		if (is_flag(str[*pos]))
		{
			if (str[*pos] == '+')
				cspec->flags |= FLAG_PLUS;
			else if (str[*pos] == '-')
				cspec->flags |= FLAG_MINUS;
			else if (str[*pos] == '0')
				cspec->flags |= FLAG_ZERO;
			else if (str[*pos] == '#')
				cspec->flags |= FLAG_HASH;
			else if (str[*pos] == ' ')
				cspec->flags |= FLAG_SPACE;
			(*pos)++;
		}
		else
			return (0);
		i++;
	}
	return (1);
}

int		parse_width(t_pf_cspec *cspec, const char *str, size_t *pos)
{
	int		width;

	if (is_wildcard(str[*pos]))
	{
		(*pos)++;
		cspec->wildcard = 1;
		return (0);
	}
	if (pf_atoi(str, &width, pos))
		return (1);
	cspec->width = width;
	return (0);
}

int		parse_prec(t_pf_cspec *cspec, const char *str, size_t *pos)
{
	int		prec;

	cspec->prec = -1;
	if (str[*pos] != '.')
		return (0);
	cspec->prec = 0;
	(*pos)++;
	if (pf_atoi(str, &prec, pos))
		return (1);
	cspec->prec = prec;
	return (0);
}

int		parse_lmod(t_pf_cspec *cspec, const char *str, size_t *pos)
{
	t_pf_lmod	lmod;

	lmod = NONE;
	if (!is_lmod(str[*pos]))
		return (0);
	if (str[*pos] == 'h')
	{
		if (str[*pos + 1] == 'h' && ++(*pos))
			lmod = HH;
		else
			lmod = H;
	}
	else if (str[*pos] == 'l')
	{
		if (str[*pos + 1] == 'l' && ++(*pos))
			lmod = LL;
		else
			lmod = L;
	}
	else if (str[*pos] == 'j')
		lmod = J;
	else if (str[*pos] == 'z')
		lmod = Z;
	cspec->lmod = lmod;
	return ((*pos)++ & 0);
}

int		parse_conv(t_pf_cspec *cspec, const char *str, size_t *pos)
{
	if (is_conv(str[*pos]))
	{
		cspec->conv = str[*pos];
		(*pos)++;
		return (0);
	}
	return (1);
}
