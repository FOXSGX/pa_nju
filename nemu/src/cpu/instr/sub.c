#include "cpu/instr.h"

make_instr_func(sub_i2rm_bv)
{
    int len = 1;
    OPERAND rm, imm;
    rm.data_size = data_size;
    len += modrm_rm(eip + 1, &rm);
    imm.data_size = 8;
    imm.type = OPR_IMM;
    imm.addr = eip + len;
    imm.sreg = SREG_CS;
    
    operand_read(&rm);
    operand_read(&imm);

    rm.val = alu_sub(sign_ext(imm.val, 8), rm.val, data_size);
    operand_write(&rm);
    return len + 1;
}
