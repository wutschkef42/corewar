/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <fwutschk@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 20:47:47 by wutschkef         #+#    #+#             */
/*   Updated: 2017/06/27 00:26:50 by fwutschk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;

	tmp = NULL;
	while (*s)
	{
		if (*s == c)
			tmp = (char *)s;
		s++;
	}
	if (c == '\0' && *s == '\0')
		return ((char *)s);
	if (tmp != NULL)
		return (tmp);
	return (NULL);
}
