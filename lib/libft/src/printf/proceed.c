/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proceed.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <felix.wutschke@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 20:10:17 by wutschkef         #+#    #+#             */
/*   Updated: 2017/12/22 20:10:23 by wutschkef        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		proceed(const char *format, size_t len, int ok, va_list params)
{
	if (ok && *format == '%')
		return (dispatch(parse_cspec(format, len), params));
	else
		return (ft_putstr(format, len));
}
