

#include "circular_doubly_linked_list.h"
#include "libft.h"
#include <stdio.h>

t_cdll_node	*cdll_new_node(void *data, size_t size)
{
	t_cdll_node *new;

	if (!(new = malloc(sizeof(t_cdll_node))))
		return (NULL);
	if (!(new->data = malloc(size)))
		return (NULL);
	ft_memcpy(new->data, data, size);
	new->size = size;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void		cdll_push_front(t_cdll_node **lst, t_cdll_node *node)
{
	t_cdll_node	*last;

	if (!*lst)
	{
		node->next = node;
		node->prev = node;
		*lst = node;
	}
	last = (*lst)->prev;	
	node->next = *lst;
	node->prev = last;
	last->next = node;
	(*lst)->prev = node;
	*lst = node;
}

void		cdll_push_back(t_cdll_node **lst, t_cdll_node *node)
{
	t_cdll_node	*last;

	if (!*lst)
	{
		node->next = node;
		node->prev = node;
		*lst = node;
	}
	last = (*lst)->prev;
	node->next = *lst;
	node->prev = last;
	(*lst)->prev = node;
	last->next = node;
}

/*
void		cdll_del_node(t_cdll_node **lst, t_cdll_node *del)
{
	t_cdll_node		*head;

	if (!*lst || !del)
		return ;
	if (*lst == del && (*lst)->next == del)
	{
		free(del);
		*lst = NULL;
		return ;
	}
	head = *lst;
	while (*lst != del && (*lst)->next != head)
		lst = &(*lst)->next;
	if ((*lst)->next == head && *lst != del) 
		return ;
	(*lst)->next->prev = (*lst)->prev;
	(*lst)->prev->next = (*lst)->next;
	if (*lst == head)
		*lst = head->next;
	free(del);
}
*/

void		cdll_del_node(t_cdll_node **head, t_cdll_node *del)
{
	t_cdll_node		*tmp;

	if (*head == del && (*head)->next == del)
		*head = NULL;
	else
	{
		tmp = *head;
		while (tmp != del && tmp->next != *head)
			tmp = tmp->next;
		if (tmp->next == *head && tmp != del) 
			return ;
		tmp->next->prev = tmp->prev;
		tmp->prev->next = tmp->next;
		if (tmp == *head)
			*head = tmp->next;
	}
	free(del);
}


void		display(t_cdll_node *lst)
{
	t_cdll_node	*tmp;

	if (!lst)
		return ;
	tmp = lst;
	while (tmp->next != lst)
	{
		printf("%s ", (char*)tmp->data);
		tmp = tmp->next;
	}
	printf("%s\n", (char*)tmp->data);
}


int			main()
{
	t_cdll_node	*lst;
	t_cdll_node	*front;
	t_cdll_node	*middle;
	t_cdll_node	*back;

	front = cdll_new_node((void*)"1", 1);
	middle = cdll_new_node((void*)"3", 1);
	back = cdll_new_node((void*)"c", 1);
	lst = NULL;
	cdll_push_front(&lst, front);
	cdll_push_front(&lst, middle);
	cdll_push_front(&lst, back);
	display(lst);
	cdll_del_node(&lst, front);
	display(lst);
	cdll_del_node(&lst, back);
	display(lst);
	cdll_del_node(&lst, middle);
	display(lst);
}