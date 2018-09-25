
#include "corewar.h"

/*
 * initializes the champion by
 * setting the pc to the champion's first instruction
 * setting the cooldown
 * setting opcode

void    init_champion()
{
    g_env.pc = 0;
    g_env.cur_op.opcode = g_mem[g_env.pc];
    g_env.cur_op.cooldown = op_tab[g_mem[g_env.pc]].cooldown;
}
*/


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
static void    set_is_alive_zero(t_process *processes)
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
static void    decrement_cooldown(t_process *processes)
{
    while (processes)
    {
        processes->cur_op.cooldown--;
        processes = processes->next;
    }
}

void    vm_loop(t_process **processes)
{
    int cycle_count;
    int cycle_to_die;

    init_cur_ops(*processes);
    cycle_to_die = CYCLE_TO_DIE;
    while (*processes)
    {
        set_is_alive_zero(*processes);
        cycle_count = 0;
        while (cycle_count < cycle_to_die)
        {
            if (g_vm.dump_flag == 0)
            {
                print_hexdump();
                exit(0);
            }
            cycle_count++;
            g_vm.dump_flag = (g_vm.dump_flag == -1) ? -1 : g_vm.dump_flag - 1;
            decrement_cooldown(*processes);
            execute_cooled_down_instructions(processes);
            fetch_new_cur_ops(*processes);
            usleep(100);
        }
        cycle_to_die -= CYCLE_DELTA;
        remove_dead_processes(processes);
    }
}