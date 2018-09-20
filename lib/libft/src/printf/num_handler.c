/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <felix.wutschke@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 20:16:58 by wutschkef         #+#    #+#             */
/*   Updated: 2017/12/22 20:18:29 by wutschkef        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	cast(t_pf_cspec cspec, va_list list)
{
	intmax_t	n;

	if (cspec.lmod == L)
		n = va_arg(list, long);
	else if (cspec.lmod == LL)
		n = va_arg(list, long long);
	else if (cspec.lmod == J)
		n = va_arg(list, intmax_t);
	else if (cspec.lmod == Z)
		n = va_arg(list, ssize_t);
	else
		n = va_arg(list, int);
	if (cspec.lmod == HH)
		n = (char)n;
	else if (cspec.lmod == H)
		n = (short)n;
	return (n);
}

int			num_handler(t_pf_cspec cspec, va_list list)
{
	char		*str;
	intmax_t	n;
	int			nwrite;
	char		sign;

	nwrite = 0;
	if (cspec.wildcard)
		cspec.width = va_arg(list, int);
	n = cast(cspec, list);
	cspec.value = &n;
	if (cspec.flags & FLAG_PLUS)
		sign = '+';
	else if (cspec.flags & FLAG_SPACE)
		sign = ' ';
	else
		sign = 0;
	if (cspec.prec == 0 && n == 0)
		str = NULL;
	else
		str = pf_itoa(n, cspec, sign);
	nwrite += print_cspec(cspec, str, ft_strlen(str), str != NULL);
	return (nwrite);
}
