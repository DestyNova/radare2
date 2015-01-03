#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <r_types_base.h>
#include "m68k_asm.c"

static void can_assemble_nop(void **state) {
  (void) state; /* unused */
  ut8 buf[4];
  int i;
  for(i = 0; i < 4; i++)
   buf[i] = 0; 
  int size = m68k_assemble(buf, 0, "nop");
  assert_int_equal(0x4E, buf[0]);
  assert_int_equal(0x71, buf[1]);
  assert_int_equal(2, size);
}

static void does_nothing_for_bad_insn(void **state) {
  (void) state; /* unused */
  ut8 buf[32];
  int i;
  for(i = 0; i < 32; i++)
   buf[i] = 0; 
  int size = m68k_assemble(buf, 0, "bad_insn");
  assert_int_equal(0x00, buf[0]);
  assert_int_equal(0x00, buf[1]);
  assert_int_equal(-1, size);
}

static void clear_buf(ut8* buf) {
  int i;
  for(i = 0; i < 4; i++)
    buf[i] = 0; 
}

static void simple_instructions(void **state) {
  (void) state; /* unused */
  ut8 buf[4];
  clear_buf(buf);

  int size = m68k_assemble(buf, 0, "addq.l #0x8,sp"); // #0x8 === 0?
  assert_int_equal(0x50, buf[0]);
  assert_int_equal(0x8F, buf[1]);
  assert_int_equal(2, size);

  clear_buf(buf);
  size = m68k_assemble(buf, 0, "addq.w #0x6,sp");
  assert_int_equal(0x5C, buf[0]);
  assert_int_equal(0x4F, buf[1]);
  assert_int_equal(2, size);

// TODO: addq to D registers
}

int main(void) {
  const UnitTest tests[] = {
    unit_test(can_assemble_nop),
    unit_test(does_nothing_for_bad_insn),
    unit_test(simple_instructions),
  };
  return run_tests(tests);
}
