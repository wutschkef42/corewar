
#include "corewar.h" 

/*								live(0x01)
 * Followed by 4 bytes representing the player name. 
 * This instruction indicates that the player is alive. (No parameter encoding byte).
 * sets the is_alive flag in processes global memory
 * CAN IT GO WRONG? DONT THINK SO
*/
//int	live(t_process **processes, t_process *active_process)
void	live(t_process **processes, t_process *active_process)
{
	unsigned int	n;

	//printf("byte1: %hhX, byte2: %hhX, byte3: %hhX, byte4: %hhX\n", VMMEM(CURPC + 1), VMMEM(CURPC + 2), VMMEM(CURPC + 3), VMMEM(CURPC + 4));
	n = (VMMEM[CURPC + 1] << 24) | ((unsigned char)(VMMEM(CURPC +2) << 16) | ((unsigned char)(VMMEM(CURPC + 3) << 8) | (unsigned char)VMMEM(CURPC + 4);	
	//printf("I'm alive %d(player_name)\n", n);
	ISALIVE = 1;
}

/*								load(0x02)
 * NOTE ld affects carry, not implemented yet // DONE
 * two cases:
 *  1. 34%,r3 -> load 34 to r3
 *  2. 34,r3  -> load value from mem address (CURPC + 34) to r3
 * This instruction takes 2 parameters, the 2nd of which has to be a register (not the PC) 
 * It loads the value of the first parameter in the register. 
 * This operation modifies the carry. 
 * ld 34,r3 loads the REG_SIZE bytes from address (PC + (34 % IDX_MOD)) in register r3.
*/
//int	ld(t_process **processes, t_process *active_process)
void	ld(t_process **processes, t_process *active_process)
{	
	if (TPARAM(1) != TREG)//takes 2 parameters, the 2nd of which has to be a register (not the PC) 
	{
		//fprintf(stderr, "wrong parameters type in instruction load");
		CARRY = 0;
		return ;
	}
	//printf("load()\n");
	if (TPARAM(0) == TIND)
	{
		REGNO(PARAM(1)) = char2int(CURPC, (PARAM(0) % IDX_MOD), REG_SIZE);
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
 *	2. r1,34 -> store value from env.r1 in mem address (CURPC + 34)
 * This instruction takes 2 parameters. 
 * It stores (REG_SIZE bytes) the value of the first argument (always a register) in the second. 
 * st r4,34 stores the value of r4 at the address (PC + (34 % IDX_MOD)) st r3,r8 copies r3 in r8
*/
void	st(t_process **processes, t_process *active_process)
{
	if (TPARAM(0) != TREG)
	{
		printf(stderr, "wrong parameters type in instruction sub");
		CARRY = 0;
		return ;
	}
	printf("store()");
	if (TPARAM(1) == TREG) // here store in register
	{
		REGNO(PARAM(1)) = REGNO(PARAM(0));
	}
	else // here store in VM memory
	{
		int2char(CURPC, 0, REG_SIZE, PARAM(0));
		//VMMEM((CURPC + PARAM(1) % IDX_MOD) % MEM_SIZE) = REGNO(PARAM(0));
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

//int	add(t_process **processes, t_process *active_process)
void	add(t_process **processes, t_process *active_process)
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
//int	sub(t_process **processes, t_process *active_process)
void	sub(t_process **processes, t_process *active_process)
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

//int	and(t_process **processes, t_process *active_process)
void	and(t_process **processes, t_process *active_process)
{
	printf("and() : ");
	if (TPARAM(2) == TREG)
	{
		if (TPARAM(0) == TREG && TPARAM(1) == TREG)
			REGNO(PARAM(2)) = REGNO(PARAM(0)) & REGNO(PARAM(1));
		else if (TPARAM(0) == TREG && TPARAM(1) == TIND)
			REGNO(PARAM(2)) = REGNO(PARAM(0)) & VMMEM((CURPC + PARAM(1) % IDX_MOD) % MEM_SIZE);
		else if (TPARAM(0) == TREG && TPARAM(1) == TDIR)
			REGNO(PARAM(2)) = REGNO(PARAM(0)) & (PARAM(1));
		else if (TPARAM(0) == TIND && TPARAM(1) == TREG)
			REGNO(PARAM(2)) = VMMEM((CURPC + PARAM(0) % IDX_MOD) % MEM_SIZE) & REGNO(PARAM(1));
		else if (TPARAM(0) == TIND && TPARAM(1) == TIND)
			REGNO(PARAM(2)) = VMMEM(CURPC + PARAM(0) % IDX_MOD) & VMMEM((CURPC + PARAM(1) % IDX_MOD) % MEM_SIZE);
		else if (TPARAM(0) == TIND && TPARAM(1) == TDIR)
			REGNO(PARAM(2)) = VMMEM((CURPC + PARAM(0) % IDX_MOD) % MEM_SIZE) & PARAM(1);
		else if (TPARAM(0) == TDIR && TPARAM(1) == TREG)
			REGNO(PARAM(2)) = PARAM(0) & REGNO(PARAM(1));
		else if (TPARAM(0) == TDIR && TPARAM(1) == TIND)
			REGNO(PARAM(2)) = PARAM(0) & VMMEM((CURPC + PARAM(1) % IDX_MOD) % MEM_SIZE);
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

//int	or(t_process **processes, t_process *active_process)
void	or(t_process **processes, t_process *active_process)
{
	printf("or() : ");
	if (TPARAM(2) == TREG)
	{
		if (TPARAM(0) == TREG && TPARAM(1) == TREG)
			REGNO(PARAM(2)) = REGNO(PARAM(0)) | REGNO(PARAM(1));
		else if (TPARAM(0) == TREG && TPARAM(1) == TIND)
			REGNO(PARAM(2)) = REGNO(PARAM(0)) | VMMEM((CURPC + PARAM(1) % IDX_MOD) % MEM_SIZE);
		else if (TPARAM(0) == TREG && TPARAM(1) == TDIR)
			REGNO(PARAM(2)) = REGNO(PARAM(0)) | (PARAM(1));
		else if (TPARAM(0) == TIND && TPARAM(1) == TREG)
			REGNO(PARAM(2)) = VMMEM((CURPC + PARAM(0) % IDX_MOD) % MEM_SIZE) | REGNO(PARAM(1));
		else if (TPARAM(0) == TIND && TPARAM(1) == TIND)
			REGNO(PARAM(2)) = VMMEM((CURPC + PARAM(0) % IDX_MOD) % MEM_SIZE) | VMMEM((CURPC + PARAM(1) % IDX_MOD) % MEM_SIZE);
		else if (TPARAM(0) == TIND && TPARAM(1) == TDIR)
			REGNO(PARAM(2)) = VMMEM((CURPC + PARAM(0) % IDX_MOD) % MEM_SIZE) | PARAM(1);
		else if (TPARAM(0) == TDIR && TPARAM(1) == TREG)
			REGNO(PARAM(2)) = PARAM(0) | REGNO((PARAM(1)));
		else if (TPARAM(0) == TDIR && TPARAM(1) == TIND)
			REGNO(PARAM(2)) = PARAM(0) | VMMEM((CURPC + PARAM(1) % IDX_MOD) % MEM_SIZE);
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

//int	xor(t_process **processes, t_process *active_process)
void	xor(t_process **processes, t_process *active_process)
{
	printf("xor() : ");
	if (TPARAM(2) == TREG)
	{
		if (TPARAM(0) == TREG && TPARAM(1) == TREG)
			REGNO(PARAM(2)) = REGNO(PARAM(0)) ^ REGNO(PARAM(1));
		else if (TPARAM(0) == TREG && TPARAM(1) == TIND)
			REGNO(PARAM(2)) = REGNO(PARAM(0)) ^ VMMEM((CURPC + PARAM(1) % IDX_MOD) % MEM_SIZE);
		else if (TPARAM(0) == TREG && TPARAM(1) == TDIR)
			REGNO(PARAM(2)) = REGNO(PARAM(0)) ^ (PARAM(1));
		else if (TPARAM(0) == TIND && TPARAM(1) == TREG)
			REGNO(PARAM(2)) = VMMEM((CURPC + PARAM(0) % IDX_MOD) % MEM_SIZE) ^ REGNO(PARAM(1));
		else if (TPARAM(0) == TIND && TPARAM(1) == TIND)
			REGNO(PARAM(2)) = VMMEM((CURPC + PARAM(0) % IDX_MOD) % MEM_SIZE) ^ VMMEM((CURPC + PARAM(1) % IDX_MOD) % MEM_SIZE);
		else if (TPARAM(0) == TIND && TPARAM(1) == TDIR)
			REGNO(PARAM(2)) = VMMEM((CURPC + PARAM(0) % IDX_MOD) % MEM_SIZE) ^ PARAM(1);
		else if (TPARAM(0) == TDIR && TPARAM(1) == TREG)
			REGNO(PARAM(2)) = PARAM(0) ^ REGNO((PARAM(1)));
		else if (TPARAM(0) == TDIR && TPARAM(1) == TIND)
			REGNO(PARAM(2)) = PARAM(0) ^ VMMEM((CURPC + PARAM(1) % IDX_MOD) % MEM_SIZE);
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
 *							zjmp(0x09)
 * Cette instruction n’est pas suivie d’octet pour décrire les
 * paramètres. Elle prend toujours un index (IND_SIZE) et fait un
 * saut à cet index si le carry est à un. Si le carry est nul, zjmp ne
 * fait rien mais consomme le même temps.
 * zjmp %23 met, si carry == 1, (PC + (23 % IDX_MOD)) dans le
 * PC.
*/

//int	(t_process **processes, t_process *active_process)
void	zjump(t_process **processes, t_process *active_process)
{
	printf("zjump(), carry = %d, old pc : %d\n", CARRY, CURPC);
	if (CARRY == 0)
		return ;
	else
			CURPC = CURPC + (char2int(CURPC, 0, IND_SIZE) % IDX_MOD);
	printf("new pc = %d\n", CURPC);
}



/* calculate position of next program counter
int	calc_next_CURPC()
{

}
TO REMOVE? NEXT PC ALREADy CALCULATED IN fetch_instruction
*/

