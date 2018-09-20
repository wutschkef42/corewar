/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <felix.wutschke@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 19:46:11 by wutschkef         #+#    #+#             */
/*   Updated: 2017/12/30 10:04:57 by wutschkef        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_conv(const char c)
{
	if (ft_strchr("%sSpdDioOuUxXcC", c))
		return (1);
	return (0);
}

int		is_lmod(const char c)
{
	if (ft_strchr("hljz", c))
		return (1);
	return (0);
}

int		is_flag(const char c)
{
	if (ft_strchr("#0-+ ", c))
		return (1);
	return (0);
}

int		is_prec(const char c)
{
	if (c == '.')
		return (1);
	return (0);
}

int		is_token(const char c)
{
	return (is_conv(c) || is_flag(c) || is_wildcard(c) ||
	is_prec(c) || is_lmod(c) || ft_isdigit(c));
}
