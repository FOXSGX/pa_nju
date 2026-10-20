#include "cpu/instr.h"

static void instr_execute_1op()
{
    operand_read(&opr_src);

    uint32_t ret_addr = opr_src.addr + opr_src.data_size / 8;
    cpu.esp -= opr_src.data_size / 8;

    OPERAND stack;
    stack.type = OPR_MEM;
    stack.sreg = SREG_SS;
    stack.data_size = opr_src.data_size;
    stack.addr = cpu.esp;
    stack.val = ret_addr;
    operand_write(&stack);

    cpu.eip += sign_ext(opr_src.val,opr_src.data_size);
}

make_instr_impl_1op(call, i, v)
