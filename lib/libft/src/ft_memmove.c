/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <fwutschk@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 19:24:04 by wutschkef         #+#    #+#             */
/*   Updated: 2017/06/27 00:24:03 by fwutschk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char *s1;
	char *s2;

	if (src < dst)
	{
		s1 = (char *)src + n - 1;
		s2 = (char *)dst + n - 1;
		while (n--)
			*s2-- = *s1--;
	}
	else
	{
		s1 = (char *)src;
		s2 = (char *)dst;
		while (n--)
			*s2++ = *s1++;
	}
	return (dst);
}
