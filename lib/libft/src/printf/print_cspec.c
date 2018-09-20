/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cspec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <felix.wutschke@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 20:06:43 by wutschkef         #+#    #+#             */
/*   Updated: 2017/12/22 20:10:00 by wutschkef        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	prefix_base(t_pf_cspec cspec, int *len, char **prefix)
{
	*len = 0;
	if ((!(cspec.flags & FLAG_HASH) ||
		(cspec.value && *(uintmax_t *)cspec.value == 0)) &&
		!((cspec.flags & FLAG_HASH) && cspec.conv == 'o') &&
		!(cspec.conv == 'p'))
		return ;
	if (cspec.conv == 'x' || cspec.conv == 'X' || cspec.conv == 'p')
	{
		*len = 2;
		*prefix = (cspec.conv == 'X' ? "0X" : "0x");
	}
	if (cspec.conv == 'o')
	{
		*len = 1;
		*prefix = "0";
	}
}

int		print_cspec(t_pf_cspec cspec, const char *str, size_t len, int not_null)
{
	int		nwrite;
	char	pad;
	int		len_prefix;
	char	*prefix;

	pad = (cspec.conv != 'd' && cspec.flags & FLAG_ZERO ? '0' : ' ');
	prefix_base(cspec, &len_prefix, &prefix);
	if (cspec.conv == 'o' && str && *str == '0')
		len_prefix = 0;
	cspec.width -= len_prefix;
	nwrite = 0;
	if (!(cspec.flags & FLAG_MINUS) && cspec.width > (int)len)
		nwrite += fill(pad, cspec.width - len);
	if (len_prefix)
		nwrite += ft_putstr(prefix, len_prefix);
	nwrite += ft_putstr(str, len);
	if ((cspec.flags & FLAG_MINUS) && cspec.width > (int)len)
		nwrite += fill(' ', cspec.width - len);
	if (cspec.conv != 's')
		if (not_null)
			free((void*)str);
	return (nwrite);
}

int		fill(const char c, size_t n)
{
	size_t	ret;

	ret = n;
	while (n--)
		write(1, &c, 1);
	return (ret);
}
