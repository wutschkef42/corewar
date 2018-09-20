/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <fwutschk@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 02:30:38 by wutschkef         #+#    #+#             */
/*   Updated: 2017/06/27 01:51:12 by fwutschk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*ns;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	ns = ft_strnew(ft_strlen(s));
	if (!ns)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ns[i] = (*f)(s[i]);
		i++;
	}
	return (ns);
}
