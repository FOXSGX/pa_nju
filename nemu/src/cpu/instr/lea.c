#include "cpu/instr.h"

make_instr_func(lea_rm2r_v)
{
    int len = 1;
    OPERAND rm, r;
    rm.data_size = data_size;
    r.data_size = data_size;

    len += modrm_r_rm(eip + 1, &r, &rm);

    r.val = rm.addr;
    operand_write(&r);

    print_asm_2("lea", "", len, &rm, &r);
    return len;
}
