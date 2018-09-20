/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_percent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <felix.wutschke@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 20:15:37 by wutschkef         #+#    #+#             */
/*   Updated: 2017/12/22 20:16:39 by wutschkef        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	escape_percent(t_pf_cspec cspec, va_list params)
{
	int		nwrite;
	char	pad;

	(void)params;
	pad = (cspec.flags & FLAG_ZERO ? '0' : ' ');
	nwrite = 0;
	if (!(cspec.flags & FLAG_MINUS) && cspec.width > 1)
		nwrite += fill(pad, cspec.width - 1);
	nwrite += write(1, "%", 1);
	if ((cspec.flags & FLAG_MINUS) && cspec.width > 1)
		nwrite += fill(pad, cspec.width - 1);
	return (nwrite);
}
