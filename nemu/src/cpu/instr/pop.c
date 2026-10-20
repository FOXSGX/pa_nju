#include "cpu/instr.h"

static void instr_execute_1op()
{   OPERAND stack;
    stack.type = OPR_MEM;
    stack.sreg = SREG_SS;
    stack.data_size = opr_src.data_size;
    stack.addr = cpu.esp;
    operand_read(&stack);

    cpu.esp += opr_src.data_size / 8;

    opr_src.val = stack.val;
    operand_write(&opr_src);
}

make_instr_impl_1op(pop, r, v)
