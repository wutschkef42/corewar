/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <fwutschk@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 06:18:54 by wutschkef         #+#    #+#             */
/*   Updated: 2017/06/27 00:24:47 by fwutschk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

inline static void	ft_putlong(long n, int fd)
{
	if (n >= 10)
		ft_putlong(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}

void				ft_putnbr_fd(int n, int fd)
{
	long	v;

	v = n;
	if (v < 0)
	{
		ft_putchar_fd('-', fd);
		v = -v;
	}
	ft_putlong(v, fd);
}
