#ifndef R2_V850_DISASM_H
#define R2_V850_DISASM_H

#define V850_INSTR_MAXLEN	24

enum v850_cmd_opcodes {
	V850_MOV	= 0x0,
	V850_NOT	= 0x1,
	V850_DIVH	= 0x2,
	V850_JMP	= 0x3,
	V850_SATSUBR	= 0x4,
	V850_SATSUB	= 0x5,
	V850_SATADD	= 0x6,
	V850_MULH	= 0x7,
	V850_OR		= 0x8,
	V850_XOR	= 0x9,
	V850_AND	= 0xA,
	V850_TST	= 0xB,
	V850_SUBR	= 0xC,
	V850_SUB	= 0xD,
	V850_ADD	= 0xE,
	V850_CMP	= 0xF,
	V850_MOV_IMM5	= 0x10,
	V850_SATADD_IMM5 = 0x11,
	V850_ADD_IMM5	= 0x12,
	V850_CMP_IMM5	= 0x13,
	V850_SHR_IMM5	= 0x14,
	V850_SAR_IMM5	= 0x15,
	V850_SHL_IMM5	= 0x16,
	V850_MULH_IMM5	= 0x17,
	V850_SLDB	= 0x18,
	V850_SSTB	= 0x1C,
	V850_SLDH	= 0x20,
	V850_SSTH	= 0x24,
	V850_SLDW	= 0x28,
	V850_SSTW	= 0x28,
	V850_BCOND	= 0x2C,
	V850_BCOND2	= 0x2D,
	V850_BCOND3	= 0x2E,
	V850_BCOND4	= 0x2F,
	V850_ADDI	= 0x30,
	V850_MOVEA	= 0x31,
	V850_MOVHI	= 0x32,
	V850_SATSUBI	= 0x33,
	V850_ORI	= 0x34,
	V850_XORI	= 0x35,
	V850_ANDI	= 0x36,
	V850_MULHI	= 0x37,
	V850_LDB	= 0x38,
	V850_LDHW	= 0x39,
	V850_STB	= 0x3A,
	V850_STHW	= 0x3B,
	V850_JARL1	= 0x3C,
	V850_JARL2	= 0x3D,
	V850_BIT_MANIP	= 0x3E,
	V850_EXT1	= 0x3F,
};

enum v850_conds {
	V850_COND_V	= 0x0,
	V850_COND_CL	= 0x1,
	V850_COND_Z	= 0x2,
	V850_COND_NH	= 0x3,
	V850_COND_SN	= 0x4,
	V850_COND_T	= 0x5,
	V850_COND_LT	= 0x6,
	V850_COND_LE	= 0x7,
	V850_COND_NV	= 0x8,
	V850_COND_NC	= 0x9,
	V850_COND_NZ	= 0xA,
	V850_COND_H	= 0xB,
	V850_COND_NS	= 0xC,
	V850_COND_SA	= 0xD,
	V850_COND_GE	= 0xE,
	V850_COND_GT	= 0xF,
};

enum v850_bit_ops {
	V850_BIT_SET1	= 0x0,
	V850_BIT_NOT1	= 0x1,
	V850_BIT_CLR1	= 0x2,
	V850_BIT_TST1	= 0x3,
};

enum v850_extension1 {
	V850_EXT_SETF	= 0x0,
	V850_EXT_LDSR	= 0x1,
	V850_EXT_STSR	= 0x2,
	V850_EXT_UNDEF1	= 0x3,
	V850_EXT_SHR	= 0x4,
	V850_EXT_SAR	= 0x5,
	V850_EXT_SHL	= 0x6,
	V850_EXT_UNDEF2	= 0x7,
	V850_EXT_TRAP	= 0x8,
	V850_EXT_HALT	= 0x9,
	V850_EXT_RETI	= 0xa,
	V850_EXT_EXT2	= 0xb,
};

enum v850_extension2 {
	V850_EXT_DI	= 0x0,
	V850_EXT_EI	= 0x4,
};

struct v850_cmd {
	unsigned type;
	char	instr[V850_INSTR_MAXLEN];
	char	operands[V850_INSTR_MAXLEN];
};

int v850_decode_command (const ut8 *instr, struct v850_cmd *cmd);
#endif /* R2_V850_DISASM_H */
