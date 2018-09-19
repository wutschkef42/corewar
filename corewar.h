
#ifndef COREWAR_H
# define COREWAR_H

#include "op.h"

/*
 * describes one instruction of the VM's instruction set
*/

typedef struct	s_op
{
	char	*mnemonic;
	int		nparams;
	int		tparams[MAX_ARGS_NUMBER];
	int		opcode;
	int		ncycles;
	char	*descr;
	int		affect_carry;
	int		index;
}				t_op;


typedef struct	s_exec_env
{
	int		regs[REG_NUMBER];
	int		pc;
	int		carry;
	char	op_code;
}				t_exec_env;

#endif
