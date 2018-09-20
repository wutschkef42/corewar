/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cspec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <felix.wutschke@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 19:49:33 by wutschkef         #+#    #+#             */
/*   Updated: 2017/12/22 22:03:27 by wutschkef        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			is_upper(t_pf_cspec cspec)
{
	if (cspec.conv == 'S' || cspec.conv == 'O' || cspec.conv == 'C' ||
		cspec.conv == 'D' || cspec.conv == 'U')
		return (1);
	return (0);
}

t_pf_cspec	simplify_conv(t_pf_cspec cspec)
{
	if (is_upper(cspec))
	{
		cspec.conv += 32;
		cspec.lmod = L;
	}
	if (cspec.conv == 'i')
		cspec.conv = 'd';
	if (cspec.conv == 'p')
		cspec.lmod = LL;
	return (cspec);
}

t_pf_cspec	parse_cspec(const char *str, size_t len)
{
	static int	(*parse[5])(t_pf_cspec *, const char *, size_t *pos) = {
		parse_flags, parse_width, parse_prec, parse_lmod, parse_conv
	};
	t_pf_cspec	cspec;
	int			i;
	size_t		pos;

	pos = 0;
	i = 0;
	cspec = init_cspec(str, len);
	while (i < 5)
	{
		if ((*parse[i])(&cspec, str + 1, &pos))
		{
			cspec.cannot_parse = 1;
			break ;
		}
		i++;
	}
	return (simplify_conv(cspec));
}
