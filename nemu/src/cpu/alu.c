#include "cpu/cpu.h"

//掩码辅助函数
uint32_t mask(size_t data_size)
{
	return 0xFFFFFFFF >> (32 - data_size);
}
//通用标志位辅助函数
void set_ZF(uint32_t res, size_t data_size)
{
	uint32_t msk = mask(data_size);
	res = res & msk;
	cpu.eflags.ZF = (res == 0);
	return;
}
void set_PF(uint32_t res)
{
	uint32_t result = res & 0xFF;
    if(result == 0||result == 3||result == 5||result == 6||result == 9||result == 10||result == 12||result == 15||result == 17||result == 18||result == 20||result == 23||result == 24||result == 27||result == 29||result == 30||result == 33||result == 34||result == 36||result == 39||result == 40||result == 43||result == 45||result == 46||result == 48||result == 51||result == 53||result == 54||result == 57||result == 58||result == 60||result == 63||result == 65||result == 66||result == 68||result == 71||result == 72||result == 75||result == 77||result == 78||result == 80||result == 83||result == 85||result == 86||result == 89||result == 90||result == 92||result == 95||result == 96||result == 99||result == 101||result == 102||result == 105||result == 106||result == 108||result == 111||result == 113||result == 114||result == 116||result == 119||result == 120||result == 123||result == 125||result == 126||result == 129||result == 130||result == 132||result == 135||result == 136||result == 139||result == 141||result == 142||result == 144||result == 147||result == 149||result == 150||result == 153||result == 154||result == 156||result == 159||result == 160||result == 163||result == 165||result == 166||result == 169||result == 170||result == 172||result == 175||result == 177||result == 178||result == 180||result == 183||result == 184||result == 187||result == 189||result == 190||result == 192||result == 195||result == 197||result == 198||result == 201||result == 202||result == 204||result == 207||result == 209||result == 210||result == 212||result == 215||result == 216||result == 219||result == 221||result == 222||result == 225||result == 226||result == 228||result == 231||result == 232||result == 235||result == 237||result == 238||result == 240||result == 243||result == 245||result == 246||result == 249||result == 250||result == 252||result == 255)  cpu.eflags.PF = 1;
    else cpu.eflags.PF = 0;
    return;
}
void set_SF(uint32_t res, size_t data_size)
{
	uint32_t msk = mask(data_size);
	res = sign_ext((res & msk),data_size);
	cpu.eflags.SF = sign(res);
	return;
}
void set_common_flags(uint32_t res, size_t data_size){
	set_ZF(res,data_size);
	set_PF(res);
	set_SF(res,data_size);
	return;
}

//add
void set_CF_add(uint32_t res, uint32_t src, size_t data_size)
{
	uint32_t msk = mask(data_size);
	res = sign_ext((res & msk),data_size);
	src = sign_ext((src & msk),data_size);
	cpu.eflags.CF = (res < src);
	return;
}
void set_OF_add(uint32_t res, uint32_t src, uint32_t dest, size_t data_size)
{
	uint32_t msk = mask(data_size);
	res = sign_ext(res & msk, data_size);
    src = sign_ext(src & msk, data_size);
    dest = sign_ext(dest & msk,data_size);
	if (sign(src) == sign(dest)){
		if (sign(res) != sign(src))
			cpu.eflags.OF = 1;
		else 
			cpu.eflags.OF = 0;
	}else cpu.eflags.OF = 0;
	return;

}
uint32_t alu_add(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_add(src, dest, data_size);
#else
	uint32_t res = dest + src;
	set_CF_add(res, src, data_size);
	set_OF_add(res, src, dest, data_size);
	set_common_flags(res, data_size);

	return res & mask(data_size);
#endif
}

//adc
void set_CF_adc(uint32_t res, uint32_t src, size_t data_size)
{
	uint32_t msk = mask(data_size);
	res = sign_ext((res & msk),data_size);
	src = sign_ext((src & msk),data_size);
	if(cpu.eflags.CF == 1) cpu.eflags.CF = (res <= src);
    else cpu.eflags.CF = (res < src);
	return;
}
void set_OF_adc(uint32_t res, uint32_t src, uint32_t dest, size_t data_size)
{
	uint32_t msk = mask(data_size);
	res = sign_ext(res & msk, data_size);
    src = sign_ext(src & msk, data_size);
    dest = sign_ext(dest & msk,data_size);
	if (sign(src) == sign(dest)){
		if (sign(res) != sign(src))
			cpu.eflags.OF = 1;
		else 
			cpu.eflags.OF = 0;
	}else cpu.eflags.OF = 0;
	return;
}
uint32_t alu_adc(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_adc(src, dest, data_size);
#else
	uint32_t res = dest + src + cpu.eflags.CF;
	set_CF_adc(res, src, data_size);
	set_OF_adc(res, src, dest, data_size);
	set_common_flags(res, data_size);

	return res & mask(data_size);
#endif
}

//sub
void set_CF_sub(uint32_t src, uint32_t dest, size_t data_size)
{
	uint32_t msk = mask(data_size);
	src = sign_ext((src & msk),data_size);
	dest = sign_ext((dest & msk),data_size);
	cpu.eflags.CF = (dest < src);
	return;
}
void set_OF_sub(uint32_t res, uint32_t src, uint32_t dest, size_t data_size)
{
	uint32_t msk = mask(data_size);
	res = sign_ext(res & msk, data_size);
    src = sign_ext(src & msk, data_size);
    dest = sign_ext(dest & msk,data_size);
	if (sign(src) != sign(dest)){
		if (sign(res) != sign(dest))
			cpu.eflags.OF = 1;
		else 
			cpu.eflags.OF = 0;
	}else cpu.eflags.OF = 0;
	return;
}
uint32_t alu_sub(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sub(src, dest, data_size);
#else
	uint32_t res = dest - src;
	set_CF_sub(src, dest, data_size);
	set_OF_sub(res, src, dest, data_size);
	set_common_flags(res, data_size);

	return res & mask(data_size);
#endif
}

//sbb
void set_CF_sbb(uint32_t src, uint32_t dest, size_t data_size)
{
	uint32_t msk = mask(data_size);
	src = sign_ext((src & msk),data_size);
	dest = sign_ext((dest & msk),data_size);
	if(cpu.eflags.CF == 1) cpu.eflags.CF = (dest <= src);
    else cpu.eflags.CF = (dest < src);
	return;
}
void set_OF_sbb(uint32_t res, uint32_t src, uint32_t dest, size_t data_size)
{
	uint32_t msk = mask(data_size);
	res = sign_ext(res & msk, data_size);
    src = sign_ext(src & msk, data_size);
    dest = sign_ext(dest & msk,data_size);
	if (sign(src) != sign(dest)){
		if (sign(res) != sign(dest))
			cpu.eflags.OF = 1;
		else 
			cpu.eflags.OF = 0;
	}else cpu.eflags.OF = 0;
	return;
}
uint32_t alu_sbb(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sbb(src, dest, data_size);
#else
	uint32_t res = dest - src - cpu.eflags.CF;
	set_CF_sbb(src, dest, data_size);
	set_OF_sbb(res, src, dest, data_size);
	set_common_flags(res, data_size);

	return res & mask(data_size);
#endif
}

//mul
void set_CF_OF_mul(uint64_t res , size_t data_size){
    res = res >> data_size;
    cpu.eflags.CF = (res != 0);
    cpu.eflags.OF = (res != 0);
    return;
}
uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mul(src, dest, data_size);
#else
	uint64_t res =
    (uint64_t)(dest & mask(data_size)) *
    (uint64_t)(src & mask(data_size));
	res = res & (0xFFFFFFFFFFFFFFFF >> (64 - 2*data_size));
	set_CF_OF_mul(res, data_size);

	return res;
#endif
}

//imul
int64_t alu_imul(int32_t src, int32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imul(src, dest, data_size);
#else
	int64_t res = 1;
	int64_t signed_src =
    (int32_t)sign_ext((uint32_t)src, data_size);
	int64_t signed_dest =
    (int32_t)sign_ext((uint32_t)dest, data_size);
	res = res * signed_dest * signed_src;
	set_CF_OF_mul(res, data_size);

	return res;
#endif
}

//div
uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_div(src, dest, data_size);
#else
	uint64_t res = dest / src;
	return res & mask(data_size);
#endif
}

//idiv
int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_idiv(src, dest, data_size);
#else
	int64_t res = dest / src;
	return (int32_t) sign_ext((uint32_t)res & mask(data_size),data_size);
#endif
}

//mod
uint32_t alu_mod(uint64_t src, uint64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mod(src, dest);
#else
	uint32_t res = dest % src;
	return res;
#endif
}

//imod
int32_t alu_imod(int64_t src, int64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imod(src, dest);
#else
	int32_t res = dest % src;
	return res;
#endif
}

//and
uint32_t alu_and(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_and(src, dest, data_size);
#else
	uint32_t res = src & dest;
	cpu.eflags.CF = 0;
	cpu.eflags.OF = 0;
	set_common_flags(res,data_size);

	return res & mask(data_size);
#endif
}

//xor
uint32_t alu_xor(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_xor(src, dest, data_size);
#else
	uint32_t res = src ^ dest;
	cpu.eflags.CF = 0;
	cpu.eflags.OF = 0;
	set_common_flags(res,data_size);
	
	return res & mask(data_size);
#endif
}

//or
uint32_t alu_or(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_or(src, dest, data_size);
#else
	uint32_t res = src | dest;
	cpu.eflags.CF = 0;
	cpu.eflags.OF = 0;
	set_common_flags(res,data_size);
	
	return res & mask(data_size);
#endif
}

//shl
uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shl(src, dest, data_size);
#else
	uint32_t res = dest << src;
	cpu.eflags.CF = (dest >> (data_size-src)) & 0x1;
	cpu.eflags.OF = (cpu.eflags.CF ^ sign(res));
	set_common_flags(res,data_size);
	
	return res & mask(data_size);
#endif
}

uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shr(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sar(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sal(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}
