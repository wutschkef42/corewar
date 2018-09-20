/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_index.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <felix.wutschke@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 20:11:14 by wutschkef         #+#    #+#             */
/*   Updated: 2017/12/22 20:11:39 by wutschkef        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	seek_conv(const char *format, int *i, int *ok)
{
	if (!format[*i])
		return (1);
	while (format[*i] && is_token(format[*i]) &&
		!is_conv(format[*i]))
		(*i)++;
	*ok = format[*i];
	if (is_token(format[*i]) && *ok)
		(*i)++;
	else
		return (1);
	return (0);
}

int	seek_cspec(const char *format, int *i, int *ok)
{
	*ok = 1;
	while (format[*i] && format[*i] != '%')
		(*i)++;
	return (1);
}
