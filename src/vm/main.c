
#include "corewar.h"


int		main(int ac, char **av)
{
	t_process	*processes;

	processes = NULL;
	op_queue = NULL;
	init_vm();
	load_champions(ac, av, &processes);
	print_process_list(processes);
	//init_op_queue(processes, &op_queue); // obsolete, cur_op now lives inside list of processes
	// now start vm loop
	vm_loop(processses);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		exit(0);
	load_binary(av[1]);
	print_hexdump();
	//exec(0);
	vm_loop();
	print_hexdump();
	return 0;
}
