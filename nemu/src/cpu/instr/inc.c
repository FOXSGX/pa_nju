#include "cpu/instr.h"

make_instr_func(inc_rm_v)
{
    int len = 1;
    OPERAND rm;
    rm.data_size = data_size;
    len += modrm_rm(eip + 1, &rm);
    operand_read(&rm);

    int old_CF = cpu.eflags.CF;
    rm.val = alu_add(1, rm.val, data_size);
    cpu.eflags.CF = old_CF;
    operand_write(&rm);
    return len;
}
