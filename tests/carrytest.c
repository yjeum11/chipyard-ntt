#include <inttypes.h>
#include <stdlib.h>
#include <time.h>
#include "rocc.h"
#define USE_ROCC
#include "multi-word/vhd128/vhd128.h"

int main() {
  uint64_t a = 0xFFFFFFFFFFFFFFFFULL;
  uint64_t b = 0xFFFFFFFFFFFFFFFFULL;
  uint64_t d = 1;
  uint64_t e = 1;
  uint64_t c, f;
  ROCC_INSTRUCTION_DSS(0, c, a, b, 0x1); // cin = 0, cout = 1
  ROCC_INSTRUCTION_DSS(0, f, d, e, 0x8); // cin = 1, cout = 0
  
  _Bool af = 1;
  _Bool bf = 1;
  _Bool cf, df;
  ROCC_INSTRUCTION_S(3, af, 0x2);
  ROCC_INSTRUCTION_S(3, af, 0x3);

  ROCC_INSTRUCTION_D(3, cf, 0x42);
  ROCC_INSTRUCTION_D(3, df, 0x43);

  uint128_t modulus = MODULUS;
  // 41538374868278621028243970639921153
  // 0x8000000000000 00000000005E0001
    
  for (int i = 0; i < 2; i++) {
    uint128_t op1 = INT128(0x7ffffffffffff, 0xffffffffffffffff);
    uint128_t op2 = INT128(0x7ffffffffffff, 0xffffffffffffffff);
    _Bool ctrl, ehc;

    uint128_t correct = (op1 + op2) % modulus;

    uint128_t obtained = addmod128(op1, op2, modulus);
    ROCC_INSTRUCTION_D(2, ehc, 0x42);
    ROCC_INSTRUCTION_D(3, ctrl, 0x43);
    printf("\ngot is %lx %lx : ", HI64(obtained), LO64(obtained));
    print_u128_u(obtained);
    printf("\nehc: %d, ctrl: %d", ehc, ctrl);
    printf("\ncorrect is %lx %lx : ", HI64(correct), LO64(correct));
    printf("\n");

    if (correct != obtained) {
      return 1;
    }
  }


  if (f == 3 && cf == 1 && df == 1) {
    return 0;
  } else {
    return 1;
  }
}
