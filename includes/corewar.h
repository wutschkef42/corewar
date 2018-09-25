
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
#define ZJUMP	9


#define REGNO(i)	active_process->exec_env.regno[i]
#define PARAM(i) 	active_process->cur_op.params.no[i]
#define TPARAM(i) 	active_process->cur_op.params.type[i]

#define CURPC		active_process->exec_env.pc
#define CARRY		active_process->exec_env.carry
#define ISALIVE		active_process->exec_env.is_alive

#define VMMEM(i) 	g_vm.vm_mem[i]
//#define CUROP(pc) 	g_vm.vm_mem[pc] //g_env.cur_op.opcode

typedef struct	s_vm
{
	int		dump_flag;
	int		nchampions;
	int		nprocesses; // tells you the max pid when forking 
	char	vm_mem[MEM_SIZE];
}				t_vm;



/*
 * parameters of current operation
*/
typedef struct	s_param
{
	int	type[MAX_ARGS_NUMBER];
	int	no[MAX_ARGS_NUMBER];
}				t_param;


/*
 * current operation of process, waiting for cooldown before being executed
*/
typedef struct	s_cur_op
{
	int		opcode;
	int		cooldown;	// remaining cooldown
	t_param params;
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
typedef struct	s_exec_env // execution environment of a process
{
	int			regno[REG_NUMBER];
	int			pc;
	int			carry;
	int			is_alive;
	//t_cur_op	cur_op;
}				t_exec_env;



/*
 * represents a champion, champions are chained together in a list
 */
typedef struct	s_process
{
	int					pid;
	int					program_number;
	char				name[PROG_NAME_LENGTH];
	t_exec_env			exec_env;
	t_cur_op			cur_op;
	struct s_process	*next;
}				t_process;



/* instructions */
void	live(t_process **processes, t_process *active_process);
void	ld(t_process **processes, t_process *active_process);
void	st(t_process **processes, t_process *active_process);
void	add(t_process **processes, t_process *active_process);
void	sub(t_process **processes, t_process *active_process);
void	and(t_process **processes, t_process *active_process);
void	or(t_process **processes, t_process *active_process);
void	xor(t_process **processes, t_process *active_process);
void	zjump(t_process **processes, t_process *active_process);

/* vm_loop.c */
void    vm_loop();

/* vm.c */
void	exec(int pc);
int		char2int(int pc, int inc, int size);
void	int2char(int pc, int inc, int size, int regno);

/* load_champions.c */
void	print_process_list(t_process *processes);
void	load_champions(int ac, char **av, t_process **processes);
void	add_to_process_list(t_process **processes, t_process *champion);
void	init_vm();

/* GLOBAL DATA */

/* representes VM memory */
char		g_mem[MEM_SIZE];

/* execution environment*/
t_exec_env	g_env;

/* parameter types */
t_param		g_params;

/* represents VM */
t_vm		g_vm;

/* jump table of instructions */
extern void (*g_ops[])(int);




#endif
