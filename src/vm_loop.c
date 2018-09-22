

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

/* calculates how many bytes the params take up */
int     size_of_params()
{
    int size;
    int i;

    size = 0;
    i = 0;
    while (i < MAX_ARGS_NUMBER)
    {
        if (TPARAM(i) == TREG)
            size += 1;
        else if (TPARAM(i) == TDIR)
            size += DIR_SIZE;
        else if (TPARAM(i) == TIND)
            size += IND_SIZE;
        i++;
    }
    return (size);
}

/* calculates how many bytes the current instruction and its parameters take up */
int     calc_instruction_size()
{
    if (CUROP == LIVE) // 1byte for opcode, 4 bytes for param, no encoding byte
        return (5);
    else if (CUROP == LOAD || CUROP == STORE || CUROP == ADD) // 1byte for opcode, 1byte for encoding, + some bytes for params
    {
        //return (4);
        return (2 + size_of_params());
    }
    return (-1); // ERROR
}

/*
 * increments pc
 * sets cooldown
 * sets opcode
*/
void    fetch_instruction()
{
    g_env.pc += calc_instruction_size();   
    CUROP = VMMEM(g_env.pc);
    g_env.cur_op.cooldown = op_tab[CUROP].cooldown;

}

/* turn the process alive */
void    start_process()
{
    g_env.is_alive = 1;
}

/* clear old parameters from parameter memory
 * necessary because for example old instruction had 3 params,
 * new instruction has only 2, so the 3rd one won't be fully overwritten by the new ones
*/
void    clear_params()
{
    memset((void*)g_params.no, 0, sizeof(g_params.no));
    memset((void*)g_params.type, 0, sizeof(g_params.type));
}

void    vm_loop()
{
    int cycle_count;
    int cycle2die;

    start_process();
    init_champion();
    cycle_count = 0;
    cycle2die =         CYCLE_TO_DIE;
    while(g_env.is_alive)
    {
        g_env.is_alive = 0;
        while (cycle_count < cycle2die)
        {
            cycle_count++;
            g_env.cur_op.cooldown--;
            if (g_env.cur_op.cooldown == 0)
            {
                // execute instruction and increment program counter
                if (CUROP == 0)
                {
                    printf("CRASH\n");
                    exit(1);
                }
                printf("-----------------------------------------------------------------------------\n");
                exec(g_env.pc);
                // get the next instruction
                fetch_instruction();
                // clear old parameters from global memory
                clear_params();
                // reset cooldown to whatever next instruction requires
                printf("-----------------------------------------------------------------------------\n");
            }
            usleep(100);   
        }
        cycle2die -= CYCLE_DELTA;
    }
}