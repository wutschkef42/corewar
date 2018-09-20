/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <felix.wutschke@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 20:18:41 by wutschkef         #+#    #+#             */
/*   Updated: 2017/12/22 20:19:12 by wutschkef        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		string_handler(t_pf_cspec cspec, va_list params)
{
	int		nwrite;
	char	*str;
	size_t	len;

	nwrite = 0;
	if (cspec.wildcard)
		cspec.width = va_arg(params, int);
	str = va_arg(params, char *);
	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	if (cspec.prec == -1)
		cspec.prec = INF;
	if (cspec.prec > (int)len)
		cspec.prec = len;
	nwrite += print_cspec(cspec, str, cspec.prec, str != NULL);
	return (nwrite);
}
