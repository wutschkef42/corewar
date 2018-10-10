
#include "libft.h"
#include "corewar.h"


static void    get_formatting(t_process *active_process)
{
    char    enc_byte;

    enc_byte = VMMEM((CURPC + 1) % MEM_SIZE);
    printf("enc_byte = %hhX\n", enc_byte);
    active_process->cur_op.params.type[0] = (enc_byte >> 6) & 0x3;
    active_process->cur_op.params.type[1] = (enc_byte >> 4) & 0x3;
    active_process->cur_op.params.type[2] = (enc_byte >> 2) & 0x3;
    printf("get_formatting(): %02X %02X %02X\n", active_process->cur_op.params.type[0], active_process->cur_op.params.type[1], active_process->cur_op.params.type[2]);

}

static void    get_params(t_process *active_process)
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
            active_process->cur_op.params.no[i] = VMMEM((CURPC + inc) % MEM_SIZE);
            inc += 1;
        }
        else if (active_process->cur_op.params.type[i] == TDIR && op_tab[CUROP].dirsize == 0)
        {
            active_process->cur_op.params.no[i] = (VMMEM((CURPC + inc) % MEM_SIZE) << 24) 
            | ((unsigned char)(VMMEM((CURPC + inc + 1) % MEM_SIZE)) << 16) | ((unsigned char)(VMMEM((CURPC + inc + 2) % MEM_SIZE)) << 8) | (unsigned char)VMMEM((CURPC + inc + 3) % MEM_SIZE);
            inc += DIR_SIZE;
        }
        else if (active_process->cur_op.params.type[i] == TIND || (active_process->cur_op.params.type[i] == TDIR && op_tab[CUROP].dirsize == 1))
        {
            active_process->cur_op.params.no[i] = char2int(CURPC, inc, IND_SIZE);
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
