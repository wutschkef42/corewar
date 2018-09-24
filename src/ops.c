
#include "corewar.h" 

/*								live(0x01)
 * Followed by 4 bytes representing the player name. 
 * This instruction indicates that the player is alive. (No parameter encoding byte).
 * sets the is_alive flag in processes global memory
 * CAN IT GO WRONG? DONT THINK SO
*/
//int	live(int pc)
void	live(int pc)
{
	unsigned int	n;

	printf("byte1: %hhX, byte2: %hhX, byte3: %hhX, byte4: %hhX\n", VMMEM(pc+1), VMMEM(pc+2), VMMEM(pc+3), VMMEM(pc+4));
	n = (g_mem[pc+1] << 24) | ((unsigned char)(g_mem[pc+2]) << 16) | ((unsigned char)(g_mem[pc+3]) << 8) | (unsigned char)g_mem[pc+4];	
	printf("I'm alive %d(player_name)\n", n);
	g_env.is_alive = 1;
	(void)pc;
}

/*								load(0x02)
 * NOTE ld affects carry, not implemented yet // DONE
 * two cases:
 *  1. 34%,r3 -> load 34 to r3
 *  2. 34,r3  -> load value from mem address (pc + 34) to r3
 * This instruction takes 2 parameters, the 2nd of which has to be a register (not the PC) 
 * It loads the value of the first parameter in the register. 
 * This operation modifies the carry. 
 * ld 34,r3 loads the REG_SIZE bytes from address (PC + (34 % IDX_MOD)) in register r3.
*/
//int	ld(int pc)
void	ld(int pc)
{	
	if (TPARAM(1) != TREG)//takes 2 parameters, the 2nd of which has to be a register (not the PC) 
	{
		fprintf(stderr, "wrong parameters type in instruction load");
		CARRY = 0;
		return ;
	}
	printf("load()\n");
	if (TPARAM(0) == TIND)
	{
		REGNO(PARAM(1)) = char2int(pc, PARAM(0) % IDX_MOD, REG_SIZE);
	}
	else if (TPARAM(0) == TDIR)
	{
		REGNO(PARAM(1)) = PARAM(0);
	}
	CARRY = 1;
}

/* 								store(0x03)
 * WARNING no input validation
 * two cases:
 *	1. r1,r2 -> store value from env.r1 in r2
 *	2. r1,34 -> store value from env.r1 in mem address (pc + 34)
 * This instruction takes 2 parameters. 
 * It stores (REG_SIZE bytes) the value of the first argument (always a register) in the second. 
 * st r4,34 stores the value of r4 at the address (PC + (34 % IDX_MOD)) st r3,r8 copies r3 in r8
*/
void	st(int pc)
{
	if (TPARAM(0) != TREG)
	{
		fprintf(stderr, "wrong parameters type in instruction sub");
		CARRY = 0;
		return ;
	}
	printf("store(), cooldown: %d\n", g_env.cur_op.cooldown);
	if (g_params.type[1] == TREG) // here store in register
	{
		REGNO(PARAM(1)) = REGNO(PARAM(0));
	}
	else // here store in VM memory
	{
		int2char();
		VMMEM(pc + PARAM(1) % IDX_MOD) = REGNO(PARAM(0));
		printf("st(): param0: %d, param1: %d, reg%d: %d\n", PARAM(0), PARAM(1), PARAM(0), REGNO(PARAM(0)));
	}
	CARRY = 1;
}

/* 								add(0x04)
 * This instruction takes 3 registers as parameter, 
 * adds the contents of the 2 first and stores the result in the third. 
 * This operation modifies the carry. 
 * add r2,r3,r5 adds r2 and r3 and stores the result in r5.
*/

//int	add(int pc)
void	add(int pc)
{
	printf("add() : adding r%d(%d) and r%d(%d)", PARAM(0), REGNO(PARAM(0)), PARAM(1), REGNO(PARAM(1)));
	if (TPARAM(0) == TREG && TPARAM(1) == TREG && TPARAM(2) == TREG)
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

/*								sub(0x05)
 * Same effect as add, but with a substraction
 * atm, sub r1,r2,r3 -> r3 = r1 - r2. Have to be confirmed
*/
//int	sub(int pc)
void	sub(int pc)
{
		printf("sub() : soustracting r%d(%d) and r%d(%d)", PARAM(0), REGNO(PARAM(0)), PARAM(1), REGNO(PARAM(1)));
	if (TPARAM(0) == TREG && TPARAM(1) == TREG && TPARAM(2) == TREG)
	{
		REGNO(PARAM(2)) = REGNO(PARAM(0)) - REGNO((PARAM(1)));
		CARRY = 1;
		printf(" storing in r%d(%d)\n",  PARAM(2), REGNO(PARAM(2)));
	//	return(1);
	}
	else
	{
		CARRY = 0;
		fprintf(stderr, "wrong parameters type in instruction sub");
	}
	//return(0);
}

/*								and(0x06)
 * p1 & p2 -> p3, the parameter 3 is always a register 
 * This operation modifies the carry. and r2, %0,r3 stores r2 & 0 in r3.
*/

//int	and(int pc)
void	and(int pc)
{
	printf("and() : ");
	if (TPARAM(2) == TREG)
	{
		if (TPARAM(0) == TREG && TPARAM(1) == TREG)
			REGNO(PARAM(2)) = REGNO(PARAM(0)) & REGNO(PARAM(1));
		else if (TPARAM(0) == TREG && TPARAM(1) == TIND)
			REGNO(PARAM(2)) = REGNO(PARAM(0)) & VMMEM(pc + PARAM(1) % IDX_MOD);
		else if (TPARAM(0) == TREG && TPARAM(1) == TDIR)
			REGNO(PARAM(2)) = REGNO(PARAM(0)) & (PARAM(1));
		else if (TPARAM(0) == TIND && TPARAM(1) == TREG)
			REGNO(PARAM(2)) = VMMEM(pc + PARAM(0) % IDX_MOD) & REGNO(PARAM(1));
		else if (TPARAM(0) == TIND && TPARAM(1) == TIND)
			REGNO(PARAM(2)) = VMMEM(pc + PARAM(0) % IDX_MOD) & VMMEM(pc + PARAM(1) % IDX_MOD);
		else if (TPARAM(0) == TIND && TPARAM(1) == TDIR)
			REGNO(PARAM(2)) = VMMEM(pc + PARAM(0) % IDX_MOD) & PARAM(1);
		else if (TPARAM(0) == TDIR && TPARAM(1) == TREG)
			REGNO(PARAM(2)) = PARAM(0) & REGNO(PARAM(1));
		else if (TPARAM(0) == TDIR && TPARAM(1) == TIND)
			REGNO(PARAM(2)) = PARAM(0) & VMMEM(pc + PARAM(1) % IDX_MOD);
		else if (TPARAM(0) == TDIR && TPARAM(1) == TDIR)
			REGNO(PARAM(2)) = PARAM(0) & PARAM(1);
		// NEED TO DOUBLE CHECK AND MAYBE TERNAIRE ALL THIS SHIT
		CARRY = 1;
		printf(" storing in r%d(%d)\n",  PARAM(2), REGNO(PARAM(2)));
	//	return(1);
	}
	else
	{
		CARRY = 0;
		fprintf(stderr, "wrong parameters type in instruction and");
	}
	//return(0);
}

/*								or(0x07)
 * Same as and but with an or (| in C)
*/

//int	or(int pc)
void	or(int pc)
{
	printf("or() : ");
	if (TPARAM(2) == TREG)
	{
		if (TPARAM(0) == TREG && TPARAM(1) == TREG)
			REGNO(PARAM(2)) = REGNO(PARAM(0)) | REGNO(PARAM(1));
		else if (TPARAM(0) == TREG && TPARAM(1) == TIND)
			REGNO(PARAM(2)) = REGNO(PARAM(0)) | VMMEM(pc + PARAM(1) % IDX_MOD);
		else if (TPARAM(0) == TREG && TPARAM(1) == TDIR)
			REGNO(PARAM(2)) = REGNO(PARAM(0)) | (PARAM(1));
		else if (TPARAM(0) == TIND && TPARAM(1) == TREG)
			REGNO(PARAM(2)) = VMMEM(pc + PARAM(0) % IDX_MOD) | REGNO(PARAM(1));
		else if (TPARAM(0) == TIND && TPARAM(1) == TIND)
			REGNO(PARAM(2)) = VMMEM(pc + PARAM(0) % IDX_MOD) | VMMEM(pc + PARAM(1) % IDX_MOD);
		else if (TPARAM(0) == TIND && TPARAM(1) == TDIR)
			REGNO(PARAM(2)) = VMMEM(pc + PARAM(0) % IDX_MOD) | PARAM(1);
		else if (TPARAM(0) == TDIR && TPARAM(1) == TREG)
			REGNO(PARAM(2)) = PARAM(0) | REGNO((PARAM(1)));
		else if (TPARAM(0) == TDIR && TPARAM(1) == TIND)
			REGNO(PARAM(2)) = PARAM(0) | VMMEM(pc + PARAM(1) % IDX_MOD);
		else if (TPARAM(0) == TDIR && TPARAM(1) == TDIR)
			REGNO(PARAM(2)) = PARAM(0) | PARAM(1);
		// NEED TO DOUBLE CHECK AND MAYBE TERNAIRE ALL THIS SHIT
		CARRY = 1;
		printf(" storing in r%d(%d)\n",  PARAM(2), REGNO(PARAM(2)));
	//	return(1);
	}
	else
	{
		CARRY = 0;
		fprintf(stderr, "wrong parameters type in instruction or");
	}
	//return(0);

}

/*								xor(0x08)
 * Same as and but with an xor (^ in C)
*/

//int	xor(int pc)
void	xor(int pc)
{
	printf("xor() : ");
	if (TPARAM(2) == TREG)
	{
		if (TPARAM(0) == TREG && TPARAM(1) == TREG)
			REGNO(PARAM(2)) = REGNO(PARAM(0)) ^ REGNO(PARAM(1));
		else if (TPARAM(0) == TREG && TPARAM(1) == TIND)
			REGNO(PARAM(2)) = REGNO(PARAM(0)) ^ VMMEM(pc + PARAM(1) % IDX_MOD);
		else if (TPARAM(0) == TREG && TPARAM(1) == TDIR)
			REGNO(PARAM(2)) = REGNO(PARAM(0)) ^ (PARAM(1));
		else if (TPARAM(0) == TIND && TPARAM(1) == TREG)
			REGNO(PARAM(2)) = VMMEM(pc + PARAM(0) % IDX_MOD) ^ REGNO(PARAM(1));
		else if (TPARAM(0) == TIND && TPARAM(1) == TIND)
			REGNO(PARAM(2)) = VMMEM(pc + PARAM(0) % IDX_MOD) ^ VMMEM(pc + PARAM(1) % IDX_MOD);
		else if (TPARAM(0) == TIND && TPARAM(1) == TDIR)
			REGNO(PARAM(2)) = VMMEM(pc + PARAM(0) % IDX_MOD) ^ PARAM(1);
		else if (TPARAM(0) == TDIR && TPARAM(1) == TREG)
			REGNO(PARAM(2)) = PARAM(0) ^ REGNO((PARAM(1)));
		else if (TPARAM(0) == TDIR && TPARAM(1) == TIND)
			REGNO(PARAM(2)) = PARAM(0) ^ VMMEM(pc + PARAM(1) % IDX_MOD);
		else if (TPARAM(0) == TDIR && TPARAM(1) == TDIR)
			REGNO(PARAM(2)) = PARAM(0) ^ PARAM(1);
		// NEED TO DOUBLE CHECK AND MAYBE TERNAIRE ALL THIS SHIT
		CARRY = 1;
		printf(" storing in r%d(%d)\n",  PARAM(2), REGNO(PARAM(2)));
	//	return(1);
	}
	else
	{
		CARRY = 0;
		fprintf(stderr, "wrong parameters type in instruction xor");
	}
	//return(0);
}

/*
 *
*/

//int	(int pc)
/*
void	(int pc)
{

}
*/


/* calculate position of next program counter
int	calc_next_pc()
{

}
TO REMOVE? NEXT PC ALREADy CALCULATED IN fetch_instruction
*/

