
#include "libft.h"
#include "corewar.h"


/* 
* convert an integer into between 1 and 4 chars
*/

void	int2char(int pc, int inc, int size, int regno)
{
	int i;

	i = 0;
	while(i < size)
	{
		VMMEM(pc + inc + size - 1 - i) = (REGNO(regno) << (i * 8)) & 0XFF;
		i++;
	}
}

/* convert between 1 and 4 chars into an integer
 * useful for storing indirect parameters in integer register
 * negative numbers must be handled separately because the leading bits must be filled with 1s
 * (unsigned char) casts are necessary to supress sign extension
*/
int		char2int(int pc, int inc, int size)
{
	unsigned int	ret;
	char			is_neg;

	is_neg = (g_vm.vm_mem[pc+inc] & 0xA0) ? 1 : 0;
	ret = 0;
	if (size == 1)
		ret = (is_neg) ? g_vm.vm_mem[pc+inc] | 0xFFFFFF << 8 : g_vm.vm_mem[pc+inc];
	else if (size == 2)
	{
		ret = (g_vm.vm_mem[pc+inc] << 8) | (unsigned char)g_vm.vm_mem[pc+inc+1];
		ret = (is_neg) ? ret | 0xFFFF << 16 : ret;
	}
	else if (size == 3)
	{
		ret = (g_vm.vm_mem[pc+inc] << 16) | ((unsigned char)(g_vm.vm_mem[pc+inc+1]) << 8) | (unsigned char)g_vm.vm_mem[pc+inc+2];
		ret = (is_neg) ? ret | 0xFF << 8 : ret;
	}
	else if (size == 4)
		ret = (g_vm.vm_mem[pc+inc] << 24) | ((unsigned char)(g_vm.vm_mem[pc+inc+1]) << 16) | ((unsigned char)(g_vm.vm_mem[pc+inc+2]) << 8) | (unsigned char)g_vm.vm_mem[pc+inc+3];	
	else
		ft_printf("ERROR: IND_SIZE too big.\n");			
	return (ret);
}
