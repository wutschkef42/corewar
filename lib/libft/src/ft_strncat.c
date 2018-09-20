/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <fwutschk@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 23:00:53 by wutschkef         #+#    #+#             */
/*   Updated: 2017/06/18 20:25:51 by wutschkef        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	char	*dst_;

	dst_ = dst;
	while (*dst)
		dst++;
	while (n-- && *src)
		*dst++ = *src++;
	*dst = '\0';
	return (dst_);
}
