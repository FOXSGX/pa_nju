#include "cpu/instr.h"

make_instr_func(push)
{
    int len = 1;
    uint32_t val = cpu.gpr[opcode & 0x7]._32;
    cpu.esp -= 4;
    OPERAND mem;
    mem.type = OPR_MEM;
    mem.data_size = 32;
    mem.sreg = SREG_SS;
    mem.addr = cpu.esp;
    mem.val = val;
    operand_write(&mem);
    return len;
}
