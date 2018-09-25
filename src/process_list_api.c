
#include "corewar.h"
#include "libft.h"


void	add_to_process_list(t_process **processes, t_process *champion)
{
	champion->next = *processes;
	*processes = champion;
}

void	print_process_list(t_process *processes)
{
	t_process *p;

	p = processes;
	while (p)
	{
		ft_printf("pid: %d, pc: %d, carry: %d, is_alive: %d\n", p->pid, p->exec_env.pc, p->exec_env.carry, p->exec_env.is_alive);
		p = p->next;
	}
}

static void	remove_process(t_process **processes, t_process *to_kill)
{
    t_process   *p;

    if (*processes == to_kill)
    {
        *processes = (*processes)->next;
        free(to_kill);
    }
    p = *processes;
    while (p)
    {
        if (p->next == to_kill)
        {
            p->next = p->next->next;
            free(to_kill);
        }
        p = p->next;
    }
}

void    remove_dead_processes(t_process **processes)
{
    t_process   *p;

    p = *processes;
    while (p)
    {
        if (p->exec_env.is_alive == 0)
            remove_process(processes, p);
        p = p->next;
    }
}