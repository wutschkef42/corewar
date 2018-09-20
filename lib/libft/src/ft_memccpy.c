/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <fwutschk@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 22:56:08 by wutschkef         #+#    #+#             */
/*   Updated: 2017/06/27 00:21:54 by fwutschk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	cc;
	unsigned char	*src_c;
	unsigned char	*dst_c;

	cc = (unsigned char)c;
	src_c = (unsigned char *)src;
	dst_c = (unsigned char *)dst;
	i = 0;
	while (i < n)
	{
		dst_c[i] = src_c[i];
		if (src_c[i] == cc)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
