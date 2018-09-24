

#include "corewar.h"



/* add operation to op queue */
void	add_op(t_op_queue	**cur_ops, t_cur_op	*new_op)
{
	t_op_queue	*new;

	if (!(new = (t_op_queue*)malloc(sizeof(t_op_queue))))
		return ;
	new->op = new_op;
	new->next = *cur_ops;
}



/* delete operation from op queue after it has been executed (cooldown = 0) */
void	del_op(t_op_queue **cur_ops, t_op_queue *op)
{

}

