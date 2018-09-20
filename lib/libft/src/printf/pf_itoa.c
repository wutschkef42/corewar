/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <felix.wutschke@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 20:23:43 by wutschkef         #+#    #+#             */
/*   Updated: 2017/12/22 22:32:39 by wutschkef        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		convert_base(const char conv)
{
	if (conv == 'x' || conv == 'X' || conv == 'p')
		return (16);
	if (conv == 'o')
		return (8);
	else
		return (10);
}

char		*pf_uitoa_base(const char conv, uintmax_t n, size_t prec)
{
	char		*str;
	int			len;
	static char	*hex = "0123456789abcdef";
	static char	*hex2 = "0123456789ABCDEF";

	len = unumlen(n, convert_base(conv));
	if (len < (int)prec)
		len = prec;
	if (!(str = malloc(len + 1)))
		return (NULL);
	str[len] = '\0';
	while (len > 0)
	{
		if (conv == 'X')
			str[len - 1] = hex2[n % (int)(convert_base(conv))];
		else
			str[len - 1] = hex[n % (int)(convert_base(conv))];
		n /= convert_base(conv);
		len--;
	}
	return (str);
}

char		*pf_itoa2(int len, char sign, char neg, uintmax_t nabs)
{
	static char	*dig = "0123456789";
	char		*str;

	if (!(str = malloc(len + neg + 1)))
		return (NULL);
	if (sign)
		str[0] = sign;
	str[len + neg] = '\0';
	while (len > 0)
	{
		str[len + neg - 1] = dig[nabs % 10];
		len--;
		nabs /= 10;
	}
	return (str);
}

char		*pf_itoa(intmax_t n, t_pf_cspec cspec, char sign)
{
	int			len;
	uintmax_t	nabs;
	char		neg;

	neg = (n < 0 || sign ? 1 : 0);
	len = numlen(n);
	if (len < cspec.prec)
		len = cspec.prec;
	if (!(cspec.flags & FLAG_MINUS) && (cspec.flags & FLAG_ZERO)
		&& len < (int)cspec.width - neg)
	{
		len = (int)cspec.width - neg;
		if (cspec.prec > 0)
			len = cspec.prec;
	}
	nabs = ft_abs(n);
	if (n < 0)
		sign = '-';
	return (pf_itoa2(len, sign, neg, nabs));
}
