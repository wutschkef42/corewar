/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <fwutschk@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 02:10:10 by wutschkef         #+#    #+#             */
/*   Updated: 2017/06/27 00:21:06 by fwutschk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*s;
	char	*r;

	if ((s = (char *)malloc(sizeof(char) * size)))
	{
		r = s;
		while (size--)
			*s++ = 0;
		return (r);
	}
	return (NULL);
}
