#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../../../../include/r_types_base.h"
#include "m68k_asm.c"

static void can_assemble_nop(void **state) {
  (void) state; /* unused */
  ut8 buf[32];
  int i;
  for(i = 0; i < 32; i++)
   buf[i] = -1; 
  m68k_assemble(buf, "nop");
  assert_int_equal(buf[0], 0x4E);
  assert_int_equal(buf[1], 0x71);
}

static void does_nothing_for_bad_insn(void **state) {
  (void) state; /* unused */
  ut8 buf[32];
  int i;
  for(i = 0; i < 32; i++)
   buf[i] = -1; 
  m68k_assemble(buf, "bad_insn");
  assert_int_equal(buf[0], 0xFF);
  assert_int_equal(buf[1], 0xFF);
}

int main(void) {
  const UnitTest tests[] = {
    unit_test(can_assemble_nop),
    unit_test(does_nothing_for_bad_insn),
  };
  return run_tests(tests);
}
