/*
 * m68k_asm.c - Assembler for the Motorola 68000 CPU
 * Copyright (C) 2015 Oisín Mac Fhearaí <denpashogai@gmail.com>
 * License: 2-clause BSD
 */

#include <stdio.h>
#include <ctype.h>
#include <r_util.h>

static struct {
  const char *name;
  char code;
} regs[] = {
  {"d0", 0},
  {"d1", 1},
  {"d2", 2},
  {"d3", 3},
  {"d4", 4},
  {"d5", 5},
  {"d6", 6},
  {"d7", 7},

  {"a0", 8},
  {"a1", 9},
  {"a2", 10},
  {"a3", 11},
  {"a4", 12},
  {"a5", 13},
  {"a6", 14},
  {"a7", 15},
  {"sp", 15},

  {"pc", 16},
  {NULL}
};

static struct {
  const char *name;
  int type;
  int args;
  const char *opcode;
} ops[] = {
  { "nop", 'N', 0, "\x4E\x71"}, // reset/illegal and other 0-args here
  { "addq.l", 'S', 2, "\x50\x00"},
  { "addq.w", 'S', 2, "\x50\x00"},
  { "addq.b", 'S', 2, "\x50\x00"},
  { NULL }
};

static void write_bits(ut8* out, int val, int position, int num_bits) {
  int shifted = val << position;
  char h_byte = (shifted >> 8) & 0xFF;
  char l_byte = shifted & 0xFF;
  //printf("val: %d, pos: %d, num_bits: %d, h_byte: %X l_byte: %X\n", val, position, num_bits, h_byte, l_byte);
  //r_mem_copyendian(&shifted, &shifted, 2, 1);
  // this will need fixing for 32-bits etc...
  if(position < 16) {
      out[0] |= h_byte;
      out[1] |= l_byte;
      //printf("post-or: out_0: %X out_1: %X\n", out[0], out[1]);
  }
}

static void write_operand_size(ut8* out, const char* instruction, int position) {
  char *dot = strchr(instruction, '.');
  int pos = dot ? dot - instruction : -1;
  if(pos >= 0 && pos < 63) {
    int size_code = 0;
    switch(instruction[pos+1]) {
      case 'l':
        size_code++;
      case 'w':
        size_code++;
      case 'b':
        write_bits(out, size_code, position, 2);
        break;
    }
  }
}

static int write_q_immediate(ut8* out, const char* q_arg) {
  int len = strlen(q_arg);
  if(len > 3) {
    int num = -1;
    // only works with hex immediates for now
    //q_arg = "#0xA";
    int ok = sscanf(q_arg+3, "%x", &num);
    //printf("ok: %d num: %d arg: %s\n", ok, num, q_arg+3);
    write_bits(out, num, 9, 3);
    return 0;
  }
  return -1;  // TODO: care about failed parse
}

static int write_addressing_mode(ut8* out, char* e_addr) {
  int len = strlen(e_addr);
  int mode = -1;
  if(len == 2) {
    // write directly to Dn / An
    switch(e_addr[0]) {
      case 'd':
        mode = 0;
        break;
      case 'a':
      case 's':
        mode = 1;
        break;
    }
  }

  if(mode >= 0)
    write_bits(out, mode, 3, 3);

  return mode;
}

static void write_effective_address(ut8* out, const char* ea_arg) {
  int i = 0;
  for (i=0; regs[i].name; i++) {
    if (!strcmp(regs[i].name, ea_arg)) {
      // code % 8, since mode field selects An or Dn regs...
      //printf("ah! reg => %s, code => %d\n", regs[i].name, regs[i].code % 8);
      write_bits(out, regs[i].code % 8, 0, 3);
    }
  }
}

static int m68k_assemble(ut8* out, ut32 pc, const char* str) {
  int size = -1;
  char *s = strdup(str);
  r_str_replace_char (s, ',', ' ');
  // reserve space for instruction and 2 operands... may need to change this
  char w0[64], w1[64], w2[64];
  *w0=*w1=*w2=0;
  sscanf (s, "%63s", w0);
  if (*w0) {
    int i;
    for (i=0; ops[i].name; i++) {
      if (!strcmp(ops[i].name, w0)) {
        memcpy(out, ops[i].opcode, 2);
        size = 2; // increase later if long displacement etc
        //printf("opcode: %x%x, size: %d\n", ops[i].opcode[0], ops[i].opcode[1], ops[i].length);
        if(ops[i].args == 1)
          sscanf(s, "%63s %63s", w0, w1);
        else if(ops[i].args == 2)
          sscanf(s, "%63s %63s %63s", w0, w1, w2);

        switch (ops[i].type) {
          int fail = 0;
          case 'S':
            // maybe better to store position + length in op struct
            write_operand_size(out, ops[i].name, 6);
            write_q_immediate(out, w1);
            fail |= write_addressing_mode(out, w2);
            write_effective_address(out, w2);
            if(fail < 0)
              size = -1;
            break;
        }
      }
    }
  }
  free(s);
  return size;
}
