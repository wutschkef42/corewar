/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <felix.wutschke@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 20:23:07 by wutschkef         #+#    #+#             */
/*   Updated: 2017/12/22 20:23:30 by wutschkef        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_atoi(const char *str, int *addr, size_t *i)
{
	int	nbr;

	nbr = 0;
	while (ft_isdigit(str[*i]))
	{
		nbr = nbr * 10 + (str[*i] - '0');
		(*i)++;
	}
	*addr = nbr;
	return (0);
}
