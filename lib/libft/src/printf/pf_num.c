/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_num.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <felix.wutschke@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 20:25:40 by wutschkef         #+#    #+#             */
/*   Updated: 2017/12/23 20:01:45 by wutschkef        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_max(int a, int b)
{
	return (a > b ? a : b);
}

uintmax_t	ft_abs(intmax_t n)
{
	return (n < 0 ? -n : n);
}

size_t		numlen(intmax_t n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

size_t		unumlen(uintmax_t n, size_t base)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= base;
		len++;
	}
	return (len);
}
