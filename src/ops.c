
#include "corewar.h"
#include <string.h> 




/* live
 * sets the is_alive flag in processes global memory
*/
void	live(int pc)
{
	unsigned int	n;

	printf("byte1: %hhX, byte2: %hhX, byte3: %hhX, byte4: %hhX\n", VMMEM(pc+1), VMMEM(pc+2), VMMEM(pc+3), VMMEM(pc+4));
	n = (g_mem[pc+1] << 24) | ((unsigned char)(g_mem[pc+2]) << 16) | ((unsigned char)(g_mem[pc+3]) << 8) | (unsigned char)g_mem[pc+4];	
	printf("I'm alive %d(player_name)\n", n);
	g_env.is_alive = 1;
	(void)pc;
}

/* load 
 * NOTE ld affects carry, not implemented yet
*/
void	ld(int pc)
{
	int tmp;
	
	printf("load()\n");
	tmp = 0;
	if (TPARAM(0) == TIND)
	{
		REGNO(PARAM(1)) = VMMEM(pc + PARAM(0));
	}
	else if (TPARAM(0) == TDIR)
	{
		REGNO(PARAM(1)) = PARAM(0);
	}
	
}

/* store
 * WARNING no input validation
 * two cases:
 *	1. r1,r2 -> store value from r1 in r2
 *	2. r1,34 -> store value from r1 in mem address (pc + 34)

*/
void	st(int pc)
{
	printf("store(), cooldown: %d\n", g_env.cur_op.cooldown);
	if (g_params.type[1] == TREG) // here store in register
	{
		REGNO(PARAM(1)) = REGNO(PARAM(0));
		//g_env.regno[g_params.no[1]] = g_env.regno[g_params.no[0]];
	}
	else // here store in VM memory
	{
		printf("st(): param0: %d, param1: %d, reg1: %d\n", PARAM(0), PARAM(1), REGNO(PARAM(0)));
		VMMEM(pc+PARAM(1)) = REGNO(PARAM(0));
	}
}

/* calculate position of next program counter
int	calc_next_pc()
{

}
*/

