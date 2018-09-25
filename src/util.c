
#include "libft.h"
#include "corewar.h"

void	print_usage()
{
	ft_printf("usage..\n");
	exit(1);
}

/* print hexdump of VM's memory */
void	print_hexdump()
{
	int	i;
	int a = 1;

	i = 0;
	ft_printf("assembled champion: \n");
	while (i < MEM_SIZE)
	{
		ft_printf("%02hhX ", g_vm.vm_mem[i]);
		i++;
		if (a % 100 == 0)
			ft_printf("\n");
		a++;
	}
}