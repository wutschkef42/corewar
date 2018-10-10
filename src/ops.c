#include "corewar.h" 

/*								live(0x01)
 * Followed by 4 bytes representing the player name. 
 * This instruction indicates that the player is alive. (No parameter encoding byte).
 * sets the is_alive flag in processes global memory
 * CAN IT GO WRONG? DONT THINK SO
*/
//int	inst_live(t_process **processes, t_process *active_process)
void	inst_live(t_process **processes, t_process *active_process)
{
	unsigned int	n;

	printf("byte1: %hhX, byte2: %hhX, byte3: %hhX, byte4: %hhX\n", VMMEM(CURPC + 1), VMMEM(CURPC + 2), VMMEM(CURPC + 3), VMMEM(CURPC + 4));
	n = (VMMEM((CURPC + 1) % MEM_SIZE) << 24) | ((unsigned char)(VMMEM(CURPC + 2) % MEM_SIZE) << 16) | ((unsigned char)(VMMEM(CURPC + 3) % MEM_SIZE) << 8) | (unsigned char)VMMEM((CURPC + 4) % MEM_SIZE);
	printf("I'm alive %d(player_name)\n", n);
	ISALIVE = 1;
	//gotta check if match with a player
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
//int	inst_ld(t_process **processes, t_process *active_process)
void	inst_ld(t_process **processes, t_process *active_process)
{	
	printf("load()\n");
	if (TPARAM(1) != TREG)//takes 2 parameters, the 2nd of which has to be a register (not the PC) 
	{
		//fprintf(stderr, "wrong parameters type in instruction load");
		CARRY = 0;
		return ;
	}
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
//int	inst_st(t_process **processes, t_process *active_process)
void	inst_st(t_process **processes, t_process *active_process)
{
	printf("store()");
	if (TPARAM(0) != TREG)
		return ;
	if (TPARAM(1) == TREG) // here store in register
		REGNO(PARAM(1)) = REGNO(PARAM(0));
	else // here store in VM memory
	{
		int2char(CURPC + (PARAM(1) % IDX_MOD), REG_SIZE, REGNO(PARAM(0)));
		//VMMEM((CURPC + PARAM(1) % IDX_MOD) % MEM_SIZE) = REGNO(PARAM(0));
		printf("st(): param0: %d, param1: %d, reg%d: %d\n", PARAM(0), PARAM(1), PARAM(0), REGNO(PARAM(0)));
	}
}

/* 								add(0x04)
 * This instruction takes 3 registers as parameter, 
 * adds the contents of the 2 first and stores the result in the third. 
 * This operation modifies the carry. 
 * add r2,r3,r5 adds r2 and r3 and stores the result in r5.
*/
//int	inst_add(t_process **processes, t_process *active_process)
void	inst_add(t_process **processes, t_process *active_process)
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
//int	inst_sub(t_process **processes, t_process *active_process)
void	inst_sub(t_process **processes, t_process *active_process)
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
//int	inst_and(t_process **processes, t_process *active_process)
void	inst_and(t_process **processes, t_process *active_process)
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
//int	inst_or(t_process **processes, t_process *active_process)
void	inst_or(t_process **processes, t_process *active_process)
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
//int	inst_xor(t_process **processes, t_process *active_process)
void	inst_xor(t_process **processes, t_process *active_process)
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

/*								zjmp(0x09)
 * Cette instruction n’est pas suivie d’octet pour décrire les
 * paramètres. Elle prend toujours un index (IND_SIZE) et fait un
 * saut à cet index si le carry est à un. Si le carry est nul, zjmp ne
 * fait rien mais consomme le même temps.
 * zjmp %23 met, si carry == 1, (PC + (23 % IDX_MOD)) dans le
 * PC.
*/
//int	inst_(t_process **processes, t_process *active_process)
void	inst_zjump(t_process **processes, t_process *active_process)
{
	printf("zjump(), carry = %d, old pc : %d\n", CARRY, CURPC);
	if (CARRY == 0)
		return ;
	else
			CURPC = (CURPC + (char2int(CURPC, 0, IND_SIZE)) % IDX_MOD) % MEM_SIZE;
	printf("new pc = %d\n", CURPC);
}

/*								ldi(0x0a)
 * This operation modifies the carry. 
 * ldi 3,%4,r1 reads IND_SIZE bytes at address: (PC + (3 % IDX_MOD)), 
 * adds 4 to this value. We will name this sum S. 
 * Read REG_SIZE bytes at address (PC + (S % IDX_MOD)), 
 * which are copied to r1. Parameters 1 and 2 are indexes.
*/
//int	inst_ldi(t_process **processes, t_process *active_process)
void	inst_ldi(t_process **processes, t_process *active_process)
{
	int sum;

	sum = 0;
	printf("i()\n");
	if(!TPARAM(0) || TPARAM(1 == TIND || TPARAM(3) != TREG))
		{
			CARRY = 0;
			return ;
		}
	if (TPARAM(0) == TREG)
		sum += REGNO(PARAM(0));
	else if (TPARAM(0) == TIND)
		sum += char2int(CURPC + (PARAM(0) % IDX_MOD), 0, IND_SIZE);//CARE NEED CIRCULAR MEMORY
	else if (TPARAM(0) == TDIR)
		sum += PARAM(0);
	if (TPARAM(1) == TREG)
		sum += REGNO(PARAM(1));
	else if (TPARAM(1) == TDIR)
		sum += PARAM(1);
	REGNO(PARAM(2)) = sum;
	CARRY = 1;
}

/*								sti(0x0b)
 * sti r2,%4,%5 sti copies REG_SIZE bytes of r2 at address (4 + 5) 
 * Parameters 2 and 3 are indexes. 
 * If they are, in fact, registers, we’ll use their contents as indexes.
 * sti r2,%4,%5 sti copie REG_SIZE octet de r2 a l’adresse (4 + 5)

*/
//int	inst_sti(t_process **processes, t_process *active_process)
void	inst_sti(t_process **processes, t_process *active_process)
{
	int sum;

	sum = 0;
	printf("sti()\n");
	if (TPARAM(0) != TREG)
		return ;
	if (TPARAM(1) == TREG)
		sum += REGNO(PARAM(1));
	else if (TPARAM(1) == TIND)
		sum += char2int(CURPC + (PARAM(1) % IDX_MOD), 0, IND_SIZE);//CARE NEED CIRCULAR MEMORY
	else if (TPARAM(1) == TDIR)
		sum += PARAM(1);
	if (TPARAM(2) == TREG)
		sum += REGNO(PARAM(2));
	else if (TPARAM(2) == TDIR)
		sum += PARAM(2);
	int2char((CURPC + sum) % MEM_SIZE, REG_SIZE, REGNO(PARAM(0)));
}

/*								fork(0x0c)
 * This instruction is not followed by a parameter encoding byte. 
 * It always takes an index and creates a new program, 
 * which is executed from address : (PC + (first parameter % IDX_MOD)). 
 * Fork %34 creates a new program. 
 * The new program inherits all of its father’s states.
*/
//int	inst_fork(t_process **processes, t_process *active_process)
void	inst_fork(t_process **processes, t_process *active_process)
{
	int i;
	t_process	*new_child;

	i = -1;
	if (!(new_child = (t_process*)malloc(sizeof(t_process))))
	{
		ft_printf("error forking process\n");
		CARRY = 0;
		return ;
	}
	new_child->pid = ++g_vm.max_pid;
	new_child->program_number = active_process->program_number;
	ft_memccpy(new_child->name, active_process->name, 0, PROG_NAME_LENGTH);
	new_child->exec_env.pc = (CURPC + (PARAM(0) % IDX_MOD)) % MEM_SIZE;
	while(++i < REG_NUMBER)
		new_child->exec_env.regno[i] = active_process->exec_env.regno[i];
	new_child->exec_env.carry = active_process->exec_env.carry;
	new_child->exec_env.is_alive = 0;
	new_child->cur_op.opcode = g_vm.vm_mem[new_child->exec_env.pc];
	new_child->cur_op.cooldown = op_tab[new_child->cur_op.opcode].cooldown;
	add_to_process_list(processes, new_child);
	CARRY = 1;
}

/*								lld(0x0d
 * Comme ld sans le %IDX_MOD Cette opération modifie le carry.
*/
//int	inst_lld(t_process **processes, t_process *active_process)
void	inst_lld(t_process **processes, t_process *active_process)
{	
	printf(" long load()\n");
	if (TPARAM(1) != TREG)//takes 2 parameters, the 2nd of which has to be a register (not the PC) 
	{
		//fprintf(stderr, "wrong parameters type in instruction load");
		CARRY = 0;
		return ;
	}
	if (TPARAM(0) == TIND)
	{
		REGNO(PARAM(1)) = char2int(CURPC, PARAM(0), REG_SIZE);
	}
	else if (TPARAM(0) == TDIR)
	{
		REGNO(PARAM(1)) = PARAM(0);
	}
	CARRY = 1;
}

/*								lldi(0x0e)
 * Same as ldi, without the % IDX_MOD 
 * This operation modifies the carry.
*/
//int	inst_lldi(t_process **processes, t_process *active_process)
void	inst_lldi(t_process **processes, t_process *active_process)
{
		int sum;

	sum = 0;
	printf("lldi () \n");
	if(!TPARAM(0) || TPARAM(1 == TIND || TPARAM(3) != TREG))
		{
			CARRY = 0;
			return ;
		}
	if (TPARAM(0) == TREG)
		sum += REGNO(PARAM(0));
	else if (TPARAM(0) == TIND)
		sum += char2int(CURPC + PARAM(0), 0, IND_SIZE);//CARE NEED CIRCULAR MEMORY
	else if (TPARAM(0) == TDIR)
		sum += PARAM(0);
	if (TPARAM(1) == TREG)
		sum += REGNO(PARAM(1));
	else if (TPARAM(1) == TDIR)
		sum += PARAM(1);
	REGNO(PARAM(2)) = sum;
	CARRY = 1;
}

/*								lfork(0x0f)
 * Same as fork, without the % IDX_MOD 
 * This operation modifies the carry.
*/
//int	inst_lfork(t_process **processes, t_process *active_process)
void	inst_lfork(t_process **processes, t_process *active_process)
{
	int i;
	t_process	*new_child;

	i = -1;
	if (!(new_child = (t_process*)malloc(sizeof(t_process))))
	{
		ft_printf("error forking process\n");
		CARRY = 0;
		return ;
	}
	new_child->pid = ++g_vm.max_pid;
	new_child->program_number = active_process->program_number;
	ft_memccpy(new_child->name, active_process->name, 0, PROG_NAME_LENGTH);
	new_child->exec_env.pc = (CURPC + PARAM(0)) % MEM_SIZE;
	while(++i < REG_NUMBER)
		new_child->exec_env.regno[i] = active_process->exec_env.regno[i];
	new_child->exec_env.carry = active_process->exec_env.carry;
	new_child->exec_env.is_alive = 0;
	new_child->cur_op.opcode = g_vm.vm_mem[(new_child->exec_env.pc) % MEM_SIZE];
	new_child->cur_op.cooldown = op_tab[new_child->cur_op.opcode].cooldown;
	add_to_process_list(processes, new_child);
	CARRY = 1;
}

/*								aff(0x10)
 * This instruction is followed by a parameter encoding byte. 
 * It takes a register and displays the character the ASCII code of which is 
 * contained in the register. 
 * (a modulo 256 is applied to this ascii code, 
 * the character is displayed on the standard output) 
 * Ex: ld %52,r3 a  r3 Displays ’*’ on the standard output
*/
//int	inst_aff(t_process **processes, t_process *active_process)
void	inst_aff(t_process **processes, t_process *active_process)
{
	printf("aff() \n");
	if (TPARAM(0) == TREG)
		ft_printf("%c", PARAM(0) % 256);
}
