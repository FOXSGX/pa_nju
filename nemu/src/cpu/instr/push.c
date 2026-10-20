#include "cpu/instr.h"

static void instr_execute_1op() 
{
    operand_read(&opr_src);
    cpu.esp -= data_size / 8;

    OPERAND stack;
    stack.type = OPR_MEM;
    stack.sreg = SREG_SS;
    stack.data_size = data_size;
    stack.addr = cpu.esp;
    stack.val = sign_ext(opr_src.val,opr_src.data_size);
    operand_write(&stack);
}

make_instr_impl_1op(push, r, v)
make_instr_impl_1op(push, rm, v)
make_instr_impl_1op(push, i, v)
make_instr_impl_1op(push, i, b)
