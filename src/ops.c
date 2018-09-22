
#include "corewar.h"
#include <string.h> 




/* 
 *							live(0x01)
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

/* 
 *							load(0x02)
 * NOTE ld affects carry, not implemented yet
 * two cases:
 *  1. 34%,r3 -> load 34 to r3
 *  2. 34,r3  -> load value from mem address (pc + 34) to r3
 * VMEM(DIR | IND) -> REGNO
*/
void	ld(int pc)
{	
	printf("load()\n");
	if (TPARAM(0) == TIND)
	{
		REGNO(PARAM(1)) = VMMEM(pc + PARAM(0));
	}
	else if (TPARAM(0) == TDIR)
	{
		REGNO(PARAM(1)) = PARAM(0);
	}	
}

/* 
 *							store(0x03)
 * WARNING no input validation
 * two cases:
 *	1. r1,r2 -> store value from env.r1 in r2
 *	2. r1,34 -> store value from env.r1 in mem address (pc + 34)
 * REGNO -> VMEM(IND) | REGNO
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
		VMMEM(pc + PARAM(1)) = REGNO(PARAM(0));
		printf("st(): param0: %d, param1: %d, reg%d: %d\n", PARAM(0), PARAM(1), PARAM(0), REGNO(PARAM(0)));
	}
}

/* 
 *							add(0x04)
 * This instruction takes 3 registers as parameter, 
 * adds the contents of the 2 first and stores the result in the third. 
 * This operation modifies the carry. 
 * add r2,r3,r5 adds r2 and r3 and stores the result in r5.
*/

//int	add(int pc)
void	add(int pc)
{
	printf("add() : adding r%d(%d) and r%d(%d)", PARAM(0), REGNO(PARAM(0)), PARAM(1), REGNO(PARAM(1)));
	if(TPARAM(0) == TREG && TPARAM(1) == TREG && PARAM(2) == TREG)
	{
		REGNO(PARAM(2)) = REGNO(PARAM(0)) + REGNO((PARAM(1)));
		CARRY = 1;
		printf(" storing in r%d(%d)\n",  PARAM(2), REGNO(PARAM(2)));
	//	return(1);
	}
	else
	{
		CARRY = 0;
		fprintf(stderr, "wrong parameters type in instruction add");
	}
	//return(0);
}

/* calculate position of next program counter
int	calc_next_pc()
{

}
*/

