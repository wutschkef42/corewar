/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wutschkef <felix.wutschke@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 15:45:06 by wutschkef         #+#    #+#             */
/*   Updated: 2017/12/23 15:45:09 by wutschkef        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	cleanup(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		ft_memdel((void **)&lst);
		lst = tmp;
	}
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*elem;
	t_list	*first;

	elem = ft_lstnew(lst->data, lst->data_size);
	if (elem == NULL)
		return (NULL);
	elem = (*f)(elem);
	first = elem;
	while (lst->next)
	{
		lst = lst->next;
		elem->next = ft_lstnew(lst->data, lst->data_size);
		if (elem->next == NULL)
		{
			cleanup(first);
			return (NULL);
		}
		elem->next = (*f)(elem->next);
		elem = elem->next;
	}
	return (first);
}
