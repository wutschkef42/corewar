
#ifndef COREWAR_H
# define COREWAR_H

#include "op.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define HEADER_SIZE 0x890

#define TREG 1
#define TDIR 2
#define TIND 3

#define LIVE	1
#define LOAD	2
#define STORE	3
#define ADD		4
#define AND		5
#define SUB 	6 
#define OR 		7 
#define XOR		8 

#define CARRY		g_env.carry
#define REGNO(i)	g_env.regno[i]
#define CUROP 		g_env.cur_op.opcode

#define PARAM(i) g_params.no[i]
#define TPARAM(i) g_params.type[i]

#define VMMEM(i) g_mem[i]

/*
 * current operation of process, waiting for cooldown before being executed
*/
typedef struct	s_cur_op
{
	int	opcode;
	int	cooldown;	// remaining cooldown
}				t_cur_op;

/*
 * describes one instruction of the VM's instruction set
*/
typedef struct	s_op
{
	char	*mnemonic;
	int		nparams;
	int		tparams[MAX_ARGS_NUMBER];
	int		opcode;
	int		cooldown;
	char	*descr;
	int		affect_carry;
	int		index;
}				t_op;


// later chain execution environments in a list
// one environment per process
// there can be arbitrarily many processes because they can fork themselves
typedef struct	s_exec_env
{
	int			regno[REG_NUMBER];
	int			pc;
	int			carry;
	char		is_alive;
	t_cur_op	cur_op;
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
void	add(int pc);
void	sub(int pc);
void	and(int pc);
void	or(int pc);
void	xor(int pc);

/* vm_loop.c */
void    vm_loop();

/* vm.c */
void	exec(int pc);



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
