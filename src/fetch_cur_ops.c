

#include "corewar.h"



/* initialize the cur_op field of each process
 * before the vm starts cycling
*/
void	init_cur_ops(t_process *processes)
{
	while (processes)
	{
		processes->cur_op.opcode = g_vm.vm_mem[(processes->exec_env.pc) % MEM_SIZE];
		processes->cur_op.cooldown = op_tab[processes->cur_op.opcode].cooldown;
		processes = processes->next;
	}
}


