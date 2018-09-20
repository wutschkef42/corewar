/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <felix.wutschke@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 20:12:48 by wutschkef         #+#    #+#             */
/*   Updated: 2017/12/22 20:15:26 by wutschkef        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	char_handler(t_pf_cspec cspec, va_list list)
{
	int		nwrite;
	int		c;
	char	pad;

	pad = ((cspec.flags & FLAG_ZERO) ? '0' : ' ');
	nwrite = 0;
	c = va_arg(list, int);
	if (!(cspec.flags & FLAG_MINUS) && cspec.width > 1)
		nwrite += fill(pad, cspec.width - 1);
	nwrite += write(1, (char*)&c, 1);
	if (cspec.flags & FLAG_MINUS && cspec.width > 1)
		nwrite += fill(' ', cspec.width - 1);
	return (nwrite);
}
