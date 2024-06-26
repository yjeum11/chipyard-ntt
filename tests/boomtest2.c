#include <inttypes.h>
#include <stdlib.h>
#include "rocc.h"
#include "vhd128/vhd128.h"

int main() {
    uint128_t a = INT128(0x7ffffffffffff, 0xffffffffffffffff);
    uint128_t b = INT128(0x7ffffffffffff, 0xffffffffffffffff);
    uint128_t m = INT128(0x8000000000000, 0x00000000005E0001);
    volatile uint64_t cl, ch, el, eh;
    volatile uint64_t ml, mh;
    volatile _Bool ehc, ctrl;

    ml = LO64(m);
    mh = HI64(m);

     ctrl = !ehc ? el > ml : ehc;

    // c[2] <- ehc
    ROCC_INSTRUCTION_S(3, ehc, 0x2);
    ROCC_INSTRUCTION_DSS(1, cl, el, ml, 0x58); // flag = c[3], cout = c[0]
                                               //
    uint128_t res = INT128(ch, cl);
    uint128_t need = (a+b) % m;
    if (res != need) {
      return 1;
    } else {
      return 0;
    }
}
