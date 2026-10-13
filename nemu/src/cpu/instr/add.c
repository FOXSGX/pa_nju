#include "cpu/instr.h"

make_instr_func(add_r2rm_v)
{
    int len = 1;
    OPERAND rm, r;
    rm.data_size = data_size;
    r.data_size = data_size;
    len += modrm_r_rm(eip + 1, &r, &rm);
    operand_read(&r);
    operand_read(&rm);

    rm.val = alu_add(r.val, rm.val, data_size);
    operand_write(&rm);
    return len;
}
