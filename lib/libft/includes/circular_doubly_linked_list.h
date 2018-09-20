

#ifndef CIRCULAR_DOUBLY_LINKED_LIST_H
# define CIRCULAR_DOUBLY_LINKED_LIST_H

#include <stdlib.h>

typedef struct				s_cdll_node
{
	void				*data;
	size_t				size;
	struct s_cdll_node	*prev;
	struct s_cdll_node	*next;
}							t_cdll_node;

void		cdll_push_front(t_cdll_node **lst, t_cdll_node *node);
void		cdll_push_back(t_cdll_node **lst, t_cdll_node *node);
void		cdll_del_node(t_cdll_node **lst, t_cdll_node *node);
t_cdll_node	*cdll_new_node(void *data, size_t size);

#endif