

#include "corewar.h"

#define PC processes->exec_env.pid


/* add operation to op queue */
void	add_op(t_op_queue	**cur_ops, t_cur_op	new_op)
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

/*
 * increments pc
 * sets cooldown
 * sets opcode
*/
void    fetch_instruction()
{
    g_env.pc += calc_instruction_size();   
    CUROP = VMMEM(g_env.pc);
    g_env.cur_op.cooldown = op_tab[CUROP].cooldown;
}



void	init_op_queue(t_process *processes, t_op_queue **op_queue)
{
	t_cur_op	cur_op;

	while (processes)
	{
		cur_op.opcode = g_mem[PC];
		cur_op.pid = processes->pid;
		cur_op.cooldown = op_tab[cur_op.opcode];
		
	}
}
