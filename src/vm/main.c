
#include "corewar.h"


int		main(int ac, char **av)
{
	t_process	*processes;
	t_op_queue	*op_queue;

	processes = NULL;
	op_queue = NULL;
	init_vm();
	load_champions(ac, av, &processes);
	print_process_list(processes);
	//init_op_queue(processes, &op_queue);
	vm_loop(processses, );
	return (0);
}