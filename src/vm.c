
#include "corewar.h"



void (*g_ops[])(t_process **processes, t_process *active_process) = {0, live, ld, st, add, sub, and, or, xor};



void	init_vm()
{
	g_vm.dump_flag = -1;
	g_vm.nchampions = 0;
	g_vm.nprocesses = 0;
}


/* read op_code from memory and store it in execution environment 
void	get_op_code(int pc)
{
	printf("get_op_code(): %02X\n", g_mem[pc]);
	g_env.cur_op.opcode = g_mem[pc];
}
*/

/*	get parameter formatting 
 *		register parameters are encoded by	01
 *		direct parameters are encoded by	10
 *		indirect parameters are encoded by	11

void	get_formatting(int pc)
{
	char	enc_byte;

	printf("get_formatting(): ");
	enc_byte = g_mem[pc+1];
	printf("enc_byte: %02hhX \n", enc_byte);
	g_params.type[0] = (enc_byte >> 6) & 0x3;
	g_params.type[1] = (enc_byte >> 4) & 0x3;
	g_params.type[2] = (enc_byte >> 2) & 0x3;
	printf("%02X %02X %02X\n", g_params.type[0], g_params.type[1], g_params.type[2]);		
}
*/


/* store parameters in registers execution environment 
 * WARNING WE ASSUME 4 BYTE REGISTERS -> Generalize later!

void	get_params(int pc)
{
	int	i;
	int	inc;

	inc = 2; // first byte of first parameter
	i = 0;
	while (g_params.type[i] != 0)
	{
		printf("g_params.type[%d] = %d\n", i, g_params.type[i]);
		if (g_params.type[i] == TREG)
		{
			g_params.no[i] = g_mem[pc+inc];
			inc += 1;
		}
		else if (g_params.type[i] == TDIR)
		{
			g_params.no[i] = (g_mem[pc+inc] << 24) 
			| ((unsigned char)(g_mem[pc+inc+1]) << 16) | ((unsigned char)(g_mem[pc+inc+2]) << 8) | (unsigned char)g_mem[pc+inc+3];
			inc += DIR_SIZE;
		}
		else if (g_params.type[i] == TIND)
		{
			g_params.no[i] = char2int(pc, inc, IND_SIZE);
			inc += IND_SIZE;
		}
		else
			break ;
		i++;
	}
	printf("get_params(): param1: %d, param2: %d, param3: %d\n", g_params.no[0], g_params.no[1], g_params.no[2]);
}
*/

/* fills execution environment (registers and op-code)  
int	decode(int pc)
{
	int inc;

	inc = 0;
	get_op_code(pc); // Can opcode and params be corrupted during cooldown
	get_formatting(pc);
	get_params(pc);
	return (inc);
}

*/

/* runs op_code on data stored in registers 
void	exec(int pc)
{
	decode(pc);
	g_ops[CUROP](pc);
}
*/

/* load binary into VM memory 
void	load_binary(char *av)
{
	int	fd;
	int n_read;
	char c;
	int i;

	i = 0;
	n_read = 0;
	fd = open(av , O_RDONLY);
	lseek(fd, HEADER_SIZE, SEEK_SET);
	while ((n_read = read(fd, &c, 1)))
		g_mem[i++] = (char)c;
}
*/



