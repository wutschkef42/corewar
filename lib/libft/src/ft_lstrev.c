
#include "libft.h"

void	ft_lstrev(t_list **lst)
{
	t_list	*cpy;
	t_list	*cur;

	if (!lst || !*lst)
		return ;
	if (!((*lst)->next))
		return ;
	cur = *lst;
	while (cur->next)
	{
		if (cur->next->next)
		{
			cpy = cur->next->next;
			cur->next->next = cur;
			cur = cur->next;
			cur->next = cpy;
		}
		else
		{
			cur->next->next = cur;
			cur = cur->next;
			*lst = cur;
		}
	}
}
