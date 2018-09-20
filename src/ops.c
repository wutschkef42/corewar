
#include "corewar.h"

#define REGNO(i) g_env.regno[i]
#define PARAM(i) g_params.no[i]
#define VMMEM(i) g_mem[i]


/* live */
void	live(int pc)
{
	int	n;

	n = (g_mem[pc+1] << 24) + (g_mem[pc+2] << 16) + (g_mem[pc+3] << 8) + g_mem[pc+4];
	printf("I'm alive %d(player_name)\n", n);
	(void)pc;
}

/* load */
void	ld(int pc)
{
	(void)pc;
}

/* store
 * WARNING no input validation
 * two cases:
 *	1. r1,r2 -> store value from r1 in r2
 *	2. r1,34 -> store value from r1 in mem address (pc + 34)

*/
void	st(int pc)
{
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

