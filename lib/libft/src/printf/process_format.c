/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <felix.wutschke@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 20:10:45 by wutschkef         #+#    #+#             */
/*   Updated: 2017/12/22 20:10:48 by wutschkef        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		process_format(const char *format, va_list params)
{
	int	i;
	int	nwrite;
	int	pos;
	int	ok;

	nwrite = 0;
	i = 0;
	while (format[i])
	{
		pos = i;
		if (format[i] == '%')
		{
			i++;
			if (seek_conv(format, &i, &ok))
				continue ;
		}
		else
			seek_cspec(format, &i, &ok);
		nwrite += proceed(format + pos, i - pos, ok, params);
	}
	return (nwrite);
}
