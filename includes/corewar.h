
#ifndef COREWAR_H
# define COREWAR_H

#include "op.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define HEADER_SIZE 0x890
#define NAME_OFFSET 4

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
#define LDI		10
#define STI		11
#define FORK	12
#define LLD		13
#define LLDI	14
#define LFORK	15
#define LFORK	15
#define AFF		16

#define REGNO(i)	active_process->exec_env.regno[i]
#define PARAM(i) 	active_process->cur_op.params.no[i]
#define TPARAM(i) 	active_process->cur_op.params.type[i]


#define VMMEM(i) g_vm.vm_mem[i]

#define CURPC		active_process->exec_env.pc
#define CARRY		active_process->exec_env.carry
#define ISALIVE		active_process->exec_env.is_alive

//#define CUROP(pc) 	g_vm.vm_mem[pc] //g_env.cur_op.opcode


typedef struct	s_vm
{
	int		dump_flag;
	int		nchampions;
	int		max_pid; // highest pid in use, needed to give new pids
	int		current_winner; // player number with the latest valid live instruction
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
void	inst_live(t_process **processes, t_process *active_process);
void	inst_ld(t_process **processes, t_process *active_process);
void	inst_st(t_process **processes, t_process *active_process);
void	inst_add(t_process **processes, t_process *active_process);
void	inst_sub(t_process **processes, t_process *active_process);
void	inst_and(t_process **processes, t_process *active_process);
void	inst_or(t_process **processes, t_process *active_process);
void	inst_xor(t_process **processes, t_process *active_process);
void	inst_zjump(t_process **processes, t_process *active_process);
void	inst_ldi(t_process **processes, t_process *active_process);
void	inst_sti(t_process **processes, t_process *active_process);
void	inst_fork(t_process **processes, t_process *active_process);
void	inst_lld(t_process **processes, t_process *active_process);
void	inst_lldi(t_process **processes, t_process *active_process);
void	inst_lfork(t_process **processes, t_process *active_process);
void	inst_aff(t_process **processes, t_process *active_process);

/* util.c */
void	print_usage();

/* vm_loop.c */
void    vm_loop();

/* vm.c */
//void	exec(int pc);
//void    exec(t_process **processes, t_process *active_process);
int		char2int(int pc, int inc, int size);
void	int2char(int pc, int size, int regno);


/* load_champions.c */
void	print_process_list(t_process *processes);
void	load_champions(int ac, char **av, t_process **processes);
void	add_to_process_list(t_process **processes, t_process *champion);
void	init_vm();

/* process_list_api.c */
void    remove_dead_processes(t_process **processes);

/* execution.c */
void    execute_cooled_down_instructions(t_process **processes);

/* fetch_instructions.c */
void    fetch_new_cur_ops(t_process *processes);

/* decode_params.c */
void    decode(t_process *active_process);

/* process_list_api.c */
void	add_to_process_list(t_process **processes, t_process *champion);
void	print_process_list(t_process *processes);
void    remove_dead_processes(t_process **processes);

/* fetch_cur_ops.c */
void	init_cur_ops(t_process *processes);

/* util.c */
void	print_hexdump();
void	print_vm_state();

/* GLOBAL DATA */

/* representes VM memory */
//char		g_mem[MEM_SIZE];

/* execution environment*/
t_exec_env	g_env;

/* parameter types */
t_param		g_params;

/* represents VM */
t_vm		g_vm;

/* jump table of instructions */
extern void (*g_ops[])(t_process **processes, t_process *active_process);
extern t_op    op_tab[17];



#endif
