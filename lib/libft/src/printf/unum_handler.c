/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unum_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <felix.wutschke@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 20:19:38 by wutschkef         #+#    #+#             */
/*   Updated: 2017/12/22 22:32:07 by wutschkef        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	ucast(t_pf_cspec cspec, va_list list)
{
	intmax_t n;

	if (cspec.lmod == L)
		n = va_arg(list, unsigned long);
	else if (cspec.lmod == LL)
		n = va_arg(list, unsigned long long);
	else if (cspec.lmod == J)
		n = va_arg(list, uintmax_t);
	else if (cspec.lmod == Z)
		n = va_arg(list, size_t);
	else
		n = va_arg(list, unsigned int);
	if (cspec.lmod == HH)
		n = (unsigned char)n;
	else if (cspec.lmod == H)
		n = (unsigned short)n;
	return (n);
}

int			unum_handler(t_pf_cspec cspec, va_list list)
{
	char		*str;
	intmax_t	n;
	int			nwrite;
	int			prec;
	int			len;

	if (cspec.conv == 'd')
		return (num_handler(cspec, list));
	nwrite = 0;
	len = 0;
	if (cspec.wildcard)
		cspec.width = va_arg(list, int);
	if (cspec.flags & FLAG_HASH || cspec.conv == 'p')
		len = (cspec.conv == 'p' ? 1 : 2);
	n = ucast(cspec, list);
	cspec.value = &n;
	prec = ft_max(cspec.prec, ((cspec.flags & FLAG_ZERO) &&
				!(cspec.flags & FLAG_MINUS) ? cspec.width - len : 0));
	str = NULL;
	if ((cspec.prec == 0 && n == 0) ||
			(cspec.conv == 'o' && n == 0 && cspec.flags & FLAG_HASH))
		str = NULL;
	else
		str = pf_uitoa_base(cspec.conv, n, prec);
	return (nwrite = print_cspec(cspec, str, ft_strlen(str), str != NULL));
}
