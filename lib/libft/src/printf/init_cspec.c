/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cspec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <felix.wutschke@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 19:49:02 by wutschkef         #+#    #+#             */
/*   Updated: 2017/12/22 19:49:16 by wutschkef        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_pf_cspec	init_cspec(const char *str, size_t len)
{
	t_pf_cspec cspec;

	cspec = (t_pf_cspec) {
		.str = (t_pf_str) { .str = str, .len = len },
		.flags = 0,
		.wildcard = 0,
		.width = 0,
		.prec = 0,
		.lmod = NONE,
		.conv = 0,
		.cannot_parse = 0
	};
	return (cspec);
}
