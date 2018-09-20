/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <fwutschk@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 23:01:19 by wutschkef         #+#    #+#             */
/*   Updated: 2017/06/27 00:25:57 by fwutschk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;

	src_len = 0;
	while (src[src_len])
		src_len++;
	dst_len = 0;
	while (*dst++)
		dst_len++;
	dst -= 1;
	if (dst_len >= size)
		return (size + src_len);
	size -= dst_len + 1;
	while (*src && size--)
		*dst++ = *src++;
	*dst = '\0';
	return (src_len + dst_len);
}
