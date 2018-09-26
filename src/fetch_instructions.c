
#include "libft.h"
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
//WE NEED TO SUBSTRACT TDIR BY THE LAST PARAM OF OP TAB * 2

/* calculates how many bytes the params take up */
static int     size_of_params(t_cur_op op)
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
static int     calc_instruction_size(t_cur_op op)
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
