
#ifndef COREWAR_H
# define COREWAR_H



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



#endif
