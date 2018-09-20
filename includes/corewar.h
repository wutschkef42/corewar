
#ifndef COREWAR_H
# define COREWAR_H

#include "op.h"
#include <stdio.h> // WARNING

#define HEADER_SIZE 0x890
#define TREG 1
#define TDIR 2
#define TIND 3



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


// later chain execution environments in a list
// one environment per process
// there can be arbitrarily many processes because they can fork themselves
typedef struct	s_exec_env
{
	int		regno[REG_NUMBER];
	int		pc;
	int		carry;
	char	op_code;
}				t_exec_env;

typedef struct	s_param
{
	int	type[MAX_ARGS_NUMBER];
	int	no[MAX_ARGS_NUMBER];
}				t_param;


/* instructions */
void	live(int pc);
void	ld(int pc);
void	st(int pc);

/* GLOBAL DATA */

/* representes VM memory */
char		g_mem[MEM_SIZE];

/* execution environment*/
t_exec_env	g_env;

/* parameter types */
t_param		g_params;

/* jump table of instructions */
extern void (*g_ops[])(int);




#endif
