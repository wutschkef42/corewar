/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <fwutschk@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 15:04:48 by wutschkef         #+#    #+#             */
/*   Updated: 2017/06/27 00:20:37 by fwutschk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *data, size_t data_size)
{
	t_list	*new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!data)
	{
		new->data = NULL;
		new->data_size = 0;
	}
	else
	{
		if (!(new->data = (void *)malloc(data_size)))
			return (NULL);
		ft_memcpy(new->data, data, data_size);
		new->data_size = data_size;
	}
	new->next = NULL;
	return (new);
}
