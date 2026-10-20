#include "cpu/instr.h"

make_instr_func(ret_near) {
    OPERAND ret_addr;
    ret_addr.type = OPR_MEM;
    ret_addr.sreg = SREG_SS;
    ret_addr.data_size = data_size;
    ret_addr.addr = cpu.esp;
    operand_read(&ret_addr);

    cpu.esp += data_size / 8;

    int prefix_len = eip - cpu.eip;
    cpu.eip = ret_addr.val - (prefix_len + 1);
    return 1;
}

make_instr_func(ret_near_imm16)
{
    // 读取 ret 后面的清理字节数
    OPERAND imm;
    imm.type = OPR_IMM;
    imm.sreg = SREG_CS;
    imm.data_size = 16;
    imm.addr = eip + 1;
    operand_read(&imm);

    // 从栈顶读取返回地址
    OPERAND ret_addr;
    ret_addr.type = OPR_MEM;
    ret_addr.sreg = SREG_SS;
    ret_addr.data_size = data_size;
    ret_addr.addr = cpu.esp;
    operand_read(&ret_addr);

    // 弹出返回地址，再清理参数
    cpu.esp += data_size / 8 + imm.val;

    // 补偿主循环随后增加的指令长度
    int prefix_len = eip - cpu.eip;
    cpu.eip = ret_addr.val - (prefix_len + 3);
    return 3;
}
