#include "cpu/instr.h"

make_instr_func(leave) {
    cpu.esp = cpu.ebp;

    OPERAND stack;
    stack.type = OPR_MEM;
    stack.sreg = SREG_SS;
    stack.data_size = data_size;
    stack.addr = cpu.esp;
    operand_read(&stack);
    OPERAND bp;
    bp.type = OPR_REG;
    bp.addr = REG_EBP;
    bp.data_size = data_size;
    bp.val = stack.val;
    operand_write(&bp);
    cpu.esp += data_size / 8;

    return 1;
}
