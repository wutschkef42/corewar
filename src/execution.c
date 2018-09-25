
#include "libft.h"
#include "corewar.h"


/* gets list of processes to be able to append new processes after fork
 * and the active_process to be executed
*/
static void    exec(t_process **processes, t_process *active_process)
{
    decode(active_process);
    g_ops[active_process->cur_op.opcode](processes, active_process);
}


void    execute_cooled_down_instructions(t_process **processes)
{
    t_process *p;

    p = *processes;
    while (p)
    {
        if (p->cur_op.cooldown == 0)
            exec(processes, p);
        p = p->next;
    }
}
