/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <felix.wutschke@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 19:46:53 by wutschkef         #+#    #+#             */
/*   Updated: 2017/12/22 19:47:28 by wutschkef        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		dispatch(t_pf_cspec cspec, va_list params)
{
	int						i;
	static t_pf_dispatch	(handle[9]) = {
		{ .conv = 's', .handler = string_handler },
		{ .conv = 'd', .handler = num_handler },
		{ .conv = 'x', .handler = unum_handler },
		{ .conv = 'X', .handler = unum_handler },
		{ .conv = 'u', .handler = unum_handler },
		{ .conv = 'o', .handler = unum_handler },
		{ .conv = 'c', .handler = char_handler },
		{ .conv = 'p', .handler = unum_handler },
		{ .conv = '%', .handler = escape_percent }
	};

	i = 0;
	while (i < 9)
	{
		if (cspec.conv == handle[i].conv)
			return (handle[i].handler(cspec, params));
		i++;
	}
	return (0);
}
