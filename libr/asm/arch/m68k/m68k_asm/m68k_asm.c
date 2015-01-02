/* m68k_asm.c - Assembler for the Motorola 68000 CPU

   Copyright (C) 2015 Oisín Mac Fhearaí

   Permission is hereby granted, free of charge, to any person
   obtaining a copy of this software and associated documentation
   files (the "Software"), to deal in the Software without
   restriction, including without limitation the rights to use, copy,
   modify, merge, publish, distribute, sublicense, and/or sell copies
   of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
   OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
   BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

   Oisín Mac Fhearaí <denpashogai@gmail.com>
   */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

static const char * const regs[18] = {
  "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7", "sp",
  "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7",
  NULL
};
static struct {
  const char *name;
  int type;
  int args;
  int n;
} ops[] = {
  { "nop", 'N', 0, 0 },
  { NULL }
};

static int m68k_assemble(ut8* out, const char* str) {
  int size = -1;
  char *s = strdup(str);
  // reserve space for up to 4 tsizeens... need to figure out max #tokens in 68k...
  char w0[32], w1[32], w2[32], w3[32];
  *w0=*w1=*w2=*w3=0;
  sscanf (s, "%31s", w0);
  if (*w0) {
    int i;
    for (i=0; ops[i].name; i++) {
      if (!strcmp(ops[i].name, w0)) {
        switch (ops[i].type) {
          case 'N': // nop
            memset(out, 0x4E, 2);
            memset(out+1, 0x71, 2);
            size = 2;
            break;
        }
      }
    }
  }
  free(s);
  return size;
}
