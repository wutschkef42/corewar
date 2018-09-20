/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <fwutschk@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 05:17:43 by wutschkef         #+#    #+#             */
/*   Updated: 2017/06/27 00:10:05 by fwutschk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_itoa(int n)
{
	char	*s;
	int		string_size;
	int		i;
	int		sign;

	sign = (n < 0) ? 1 : 0;
	string_size = 1;
	i = n;
	while ((i = i / 10))
		string_size++;
	if (!(s = (char *)malloc(sizeof(char) * (string_size + sign + 1))))
		return (NULL);
	s[string_size + sign] = '\0';
	if (sign)
		s[0] = '-';
	i = string_size + sign - 1;
	while (i != (-1 + sign))
	{
		s[i--] = (sign) ? HEXTABLE(-(n % 10)) : HEXTABLE((n % 10));
		n /= 10;
	}
	return (s);
}
