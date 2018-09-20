/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <fwutschk@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 23:03:14 by wutschkef         #+#    #+#             */
/*   Updated: 2017/06/27 00:27:23 by fwutschk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	char *a;
	char *b;

	if (*s2 == '\0')
		return ((char *)s1);
	while (*s1)
	{
		a = (char *)s1;
		b = (char *)s2;
		while (*b && *a == *b)
		{
			a++;
			b++;
		}
		if (*b == '\0')
			return ((char *)s1);
		s1++;
	}
	return (NULL);
}
