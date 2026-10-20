#include "cpu/instr.h"

static void instr_execute_1op() 
{
	operand_read(&opr_src);
    uint32_t oldCF = cpu.eflags.CF;

	opr_src.val = alu_add(0x1,opr_src.val,opr_src.data_size);
    cpu.eflags.CF = oldCF;
    
    operand_write(&opr_src);
}

make_instr_impl_1op(inc, r, v)
make_instr_impl_1op(inc, rm, v)
