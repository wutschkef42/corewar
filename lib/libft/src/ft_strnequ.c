/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <fwutschk@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 02:45:17 by wutschkef         #+#    #+#             */
/*   Updated: 2017/06/27 01:52:46 by fwutschk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (!s1 || !s2)
		return (0);
	while (n--)
	{
		if (*s1 != *s2)
			return (0);
		else if (*s1 == '\0')
			return (1);
		s1++;
		s2++;
		n--;
	}
	return (1);
}
