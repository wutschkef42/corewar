

#include "libft.h"
#include "corewar.h"




/* load binary into VM memory */
static void	load_binary(char *av, int mem_address)
{
	int	fd;
	int nread;
	int	total_read;
	char c;
	int i;
	
	ft_printf("load_binary()\n");
	total_read = 0;
	i = mem_address;
	nread = 0;
	fd = open(av , O_RDONLY);
	lseek(fd, HEADER_SIZE, SEEK_SET);
	while ((nread = read(fd, &c, 1)))
	{
		total_read += nread;
		g_vm.vm_mem[i++] = (char)c;
		if (total_read > CHAMP_MAX_SIZE)
		{
			ft_printf("champion too big...\n");
			exit(1);
		}
	}
}


/*
** calculate memory address
**  
*/
static void	load_champion(int *nchampion, int *cur_arg, char **av, t_process **processes)
{
	ft_printf("load champion\n");
	t_process	*champion;

	if (!(champion = (t_process*)malloc(sizeof(t_process))))
	{
		ft_printf("error loading champion\n");
		exit(1);
	}
	champion->pid = *nchampion;
	ft_printf("nchampion: %d\n", *nchampion);
	champion->exec_env.pc = MEM_SIZE * (*nchampion - 1) / g_vm.nchampions;
	champion->exec_env.is_alive = 1;
	ft_printf("pc = %d\n", champion->exec_env.pc);
	load_binary(av[*cur_arg], champion->exec_env.pc);
	add_to_process_list(processes, champion);
	g_vm.nprocesses += 1;
	*cur_arg += 1;
	*nchampion += 1;

}

/*
** calculate number of champions to be loaded
*/
static void	calc_nchampions(int ac, char **av)
{
	int	nchampions;
	int	cur_arg;

	cur_arg = 1;
	nchampions = 0;
	if (ft_strcmp(av[cur_arg], "-dump") == 0)
		cur_arg +=2;
	g_vm.nchampions = ac - cur_arg;
}


/*
** loads binaries into VM memory
*/
void	load_champions(int ac, char **av, t_process **processes)
{
	int	i;
	int	nchampion;
	int	cur_arg;

	nchampion = 1;
	cur_arg = 1;
	if (ac < 2)
		print_usage();
	if (ft_strcmp(av[cur_arg], "-dump") == 0)
	{
		cur_arg++;
		g_vm.dump_flag = (ft_atoi(av[cur_arg]) >= 0) ? ft_atoi(av[cur_arg]) : -1;
		cur_arg++;
	}
	if (ac - cur_arg > MAX_PLAYERS)
	{
		ft_printf("Too many champions\n");
		exit(1);
	}
	calc_nchampions(ac, av);
	while (cur_arg < ac)
	{
		load_champion(&nchampion, &cur_arg, av, processes);
	}	
}
