/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <fwutschk@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 02:37:17 by wutschkef         #+#    #+#             */
/*   Updated: 2017/06/27 01:51:23 by fwutschk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ns;

	if (!s || !f)
		return (NULL);
	ns = ft_strnew(ft_strlen(s));
	if (!ns)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ns[i] = (*f)(i, s[i]);
		i++;
	}
	return (ns);
}
