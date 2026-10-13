#include "cpu/instr.h"

make_instr_func(cmp_i2rm_bv)
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

    alu_sub(sign_ext(imm.val, 8), rm.val, data_size);
    return len + 1;
}

make_instr_func(cmp_i2a_b)
{
    int len = 1;
    OPERAND rm, imm;
    rm.data_size = 8;
    rm.type = OPR_REG;
    rm.addr = REG_AL;
    imm.data_size = 8;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    imm.sreg = SREG_CS;

    operand_read(&rm);
    operand_read(&imm);

    alu_sub(imm.val, rm.val, 8);
    return len + 1;

}

make_instr_func(cmp_i2rm_v)
{
    int len = 1;
    OPERAND imm, rm;
    imm.type = OPR_IMM;
    imm.sreg = SREG_CS;
    imm.data_size = data_size;
    rm.data_size = data_size;
    len += modrm_rm(eip + 1, &rm);
    imm.addr = eip + len;

    operand_read(&rm);
    operand_read(&imm);

    alu_sub(imm.val, rm.val, data_size);
    return len + data_size / 8;
}

make_instr_func(cmp_r2rm_v)
{
    int len = 1;
    OPERAND r, rm;
    r.data_size = data_size;
    rm.data_size = data_size;
    len += modrm_r_rm(eip + 1, &r, &rm);

    operand_read(&r);
    operand_read(&rm);

    alu_sub(r.val, rm.val, data_size);
    return len;
}
