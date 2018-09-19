
#include "corewar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

/* global array representing VM memory */
char		g_mem[MEM_SIZE];

/* execution environment*/
t_exec_env	g_env;

/* parameter types */
int			g_param_types[MAX_ARGS_NUMBER];

/* read op_code from memory and store it in execution environment */
void	get_op_code(int pc)
{
	printf("get_op_code(): %c\n", g_mem[pc]);
	g_env.op_code = g_mem[pc];
}


/* get formatting information */
void	get_formatting(int pc)
{
	char	enc_byte;

	printf("get_formatting(): ");
	enc_byte = g_mem[pc+1];
	g_param_types[0] = (enc_byte >> 6) & 0x4;
	g_param_types[1] = (enc_byte >> 4) & 0x4;
	g_param_types[2] = (enc_byte >> 2) & 0x4;
	printf("%d %d %d\n", g_param_types[0], g_param_types[1], g_param_types[2]);	
}

/* store parameters in registers execution environment */
void	get_params(int pc)
{
	int	i;
	int	inc;

	inc = 2; // first byte of first parameter
	i = 0;
	while (g_param_types[i] != 0)
	{
		if (g_param_types[i] == 1)
		{
			g_env.regs[i] = g_mem[pc+inc];
			inc += 1;
		}
		else if (g_param_types[i] == 2)
		{
			memcpy(&g_env.regs[i], &g_mem[pc+inc], DIR_SIZE);
			inc += DIR_SIZE;
		}
		else if (g_param_types[i] == 4)
		{
			memcpy(&g_env.regs[i], &g_mem[pc+inc], IND_SIZE);
			inc += IND_SIZE;
		}
		else
			break ;
		i++;
	}
	printf("get_params(): reg1: %d, reg2: %d, reg3: %d\n", g_env.regs[0], g_env.regs[1], g_env.regs[2]);

}

/* fills execution environment (registers and op-code)  */
void	decode(int pc)
{
	get_op_code(pc);
	get_formatting(pc);
	get_params(pc);
}

/* runs op_code on data stored in registers 
int	exec()
{

}
*/

/* load binary into VM memory */
void	load_binary()
{
	int	fd;
	int n_read;
	char c;
	int i;

	i = 0;
	n_read = 0;
	fd = open("binary.cor" , O_RDONLY);
	lseek(fd, 2192, SEEK_SET);
	while ((n_read = read(fd, &c, 1)))
			g_mem[i++] = c;
}

int	main(int ac, char **av)
{
	load_binary();
	printf("> %s\n", g_mem);
	return 0;
}
