
#include "corewar.h"

t_op    op_tab[17] =
{
	{0, 0, {0}, 0, 0, 0, 0, 0},
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0}
};

/*
 * initializes the champion by
 * setting the pc to the champion's first instruction
 * setting the cooldown
 * setting opcode
*/
void    init_champion()
{
    g_env.pc = 0;
    g_env.cur_op.opcode = g_mem[g_env.pc];
    g_env.cur_op.cooldown = op_tab[g_mem[g_env.pc]].cooldown;
}



/*
void    vm_loop(t_process *processes)
{
    int cycle_count;
    int cycle2die;

    start_process();
    init_champion();
    cycle_count = 0;
    cycle2die = CYCLE_TO_DIE;
    while(g_env.is_alive) // while (processes)
    {
        g_env.is_alive = 0; // set is_alive = 0 for all processes
        while (cycle_count < cycle2die)
        {
            cycle_count++;
            g_env.cur_op.cooldown--; // decrement cooldown for all processes active ops
            if (g_env.cur_op.cooldown == 0) // execute all ops with cooldown = 0 in correct order -> make execute(t_process *processes)
            {
                printf("-----------------------------------------------------------------------------\n");
                exec(g_env.pc);
                // get the next instruction
                fetch_instruction(); // fetch new instructions for all processes where cooldown = 0 
                // set corrupted opcodes to -1, in order to prevent the PC from doing nonsense
                // clear old parameters from global memory
                clear_params(); // clear params for all processes where cooldown = 0

                // reset cooldown to whatever next instruction requires
                printf("-----------------------------------------------------------------------------\n");
            }
            usleep(100);   
        }
        cycle2die -= CYCLE_DELTA;
        // kill all processes that didn't claim alive
    }
}
*/


/*
 * set the is_alive flag of each process to 0
*/
void    set_is_alive_zero(t_process *processes)
{
    while (processes)
    {
        processes->exec_env.is_alive = 0;
        processes = processes->next;
    }
}

/*
 * decrement the cooldown of each processes' current operation by one
*/
void    decrement_cooldown(t_process *processes)
{
    while (processes)
    {
        processes->cur_op.cooldown--;
        processes = processes->next;
    }
}


void    get_formatting(t_process *active_process)
{
    char    enc_byte;

    
    active_process->cur_op.params.type[0] = (enc_byte >> 6) & 0x3;
    active_process->cur_op.params.type[1] = (enc_byte >> 4) & 0x3;
    active_process->cur_op.params.type[2] = (enc_byte >> 2) & 0x3;
    printf("%02X %02X %02X\n", active_process->cur_op.params.type[0], active_process->cur_op.params.type[1], active_process->cur_op.params.type[2]);

}

void    get_params(t_process *active_process)
{
    int i;
    int inc;

    inc = 2; // first byte of first parameter
    i = 0;
    while (active_process->cur_op.params.type[i] != 0)
    {
        printf("g_params.type[%d] = %d\n", i, active_process->cur_op.params.type[i]);
        if (active_process->cur_op.params.type[i] == TREG)
        {
            active_process->cur_op.params.no[i] = g_mem[pc+inc];
            inc += 1;
        }
        else if (active_process->cur_op.params.type[i] == TDIR)
        {
            active_process->cur_op.params.no[i] = (g_mem[pc+inc] << 24) 
            | ((unsigned char)(g_mem[pc+inc+1]) << 16) | ((unsigned char)(g_mem[pc+inc+2]) << 8) | (unsigned char)g_mem[pc+inc+3];
            inc += DIR_SIZE;
        }
        else if (active_process->cur_op.params.type[i] == TIND)
        {
            active_process->cur_op.params.no[i] = char2int(pc, inc, IND_SIZE);
            inc += IND_SIZE;
        }
        else
            break ;
        i++;
    }
    printf("get_params(): param1: %d, param2: %d, param3: %d\n", active_process->cur_op.params.no[0], active_process->cur_op.params.no[1], active_process->cur_op.params.type[2]);
}

void    decode(t_process *active_process)
{
    get_formatting(active_process);
    get_params(active_process);
}

/* gets list of processes to be able to append new processes after fork
 * and the active_process to be executed
*/
void    exec(t_process **processes, t_process *active_process)
{
    decode(active_process);
    g_ops[active_process->cur_op.opcode](processes, active_process);
}




/* calculates how many bytes the params take up */
int     size_of_params(t_cur_op op)
{
    int size;
    int i;

    size = 0;
    i = 0;
    while (i < MAX_ARGS_NUMBER)
    {
        if (op.params.type[i] == TREG)
            size += 1;
        else if (op.params.type[i] == TDIR)
            size += DIR_SIZE;
        else if (op.params.type[i] == TIND)
            size += IND_SIZE;
        i++;
    }
    return (size);
}



/* calculates how many bytes the current instruction and its parameters take up */
int     calc_instruction_size(t_cur_op op)
{
    if (op.opcode == LIVE) // 1byte for opcode, 4 bytes for param, no encoding byte
        return (5);
    else if (op.opcode == LOAD || op.opcode == STORE || op.opcode == ADD || op.opcode == SUB
    || op.opcode == AND || op.opcode == OR || op.opcode == XOR) // 1byte for opcode, 1byte for encoding, + some bytes for params
    {
        return (2 + size_of_params(op));
    }
    return (-1); // ERROR
}

/*
 * fetch new instructions for all processes whose cur_op has been executed on the last cycle
 *
 * increments pc
 * sets cooldown
 * sets opcode
*/
void    fetch_new_cur_ops(t_process *processes)
{
    while (processes)
    {
        if (processes->cur_op.cooldown == 0)
        {
            processes->exec_env.pc += calc_instruction_size(processes->cur_op);
            processes->cur_op.opcode = VMMEM(processes->exec_env.pc);
            processes->cur_op.cooldown = op_tab[processes->cur_op.opcode].cooldown; // !!! POTENTIAL BUS ERROR
            memset((void*)processes->cur_op.params.no, 0, sizeof(processes->cur_op.params.no)); // reset cooled down params
            memset((void*)processes->cur_op.params.type, 0, sizeof(processes->cur_op.params.type)); // reset cooled down params
        }
        processes = processes->next;
    }
}


void    execute_cooled_down_instructions(t_process **processes)
{
    t_processes *p;

    p = *processes;
    while (p)
    {
        if (p->cur_op.cooldown == 0)
            exec(processes, p);
        p = p->next;
    }
}

void    remove_process(t_process **processes, t_process *to_kill)
{
    t_process   *p;

    if (*processes = to_kill)
    {
        *processes = (*processes)->next;
        free(to_kill);
    }
    p = *processes;
    while (p)
    {
        if (p->next == to_kill)
        {
            p->next = p->next-next;
            free(to_kill);
        }
        p = p->next;
    }
}

void    remove_dead_processes(t_process **processes)
{
    t_process   *p;

    p = *processes;
    while (p)
    {
        if (p->exec_env.is_alive == 0)
            remove_process(processes, p);
        p = p->next;
    }
}

void    vm_loop(t_process **processes)
{
    int cycle_count;
    int cycle_to_die;

    while (processes)
    {
        set_is_alive_zero(*processes);
        while (cycle_count < cycle_to_die)
        {
            cycle_count++;
            decrement_cooldown(*processes);
            execute_cooled_down_instructions(processes);
            fetch_new_cur_ops(*processes);
            usleep(100);
        }
        cycle_to_die -= CYCLE_DELTA;
        remove_dead_processes(processes);
    }
}