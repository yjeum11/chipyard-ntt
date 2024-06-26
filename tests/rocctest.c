#include <stdio.h>
#include <inttypes.h>
#include "rocc.h"

int main(void) {
    volatile int a, b, c;
    a = 3;
    b = 3;
    ROCC_INSTRUCTION_DSS(0, c, a, b, 0x0);
  
    if (c == 6) {
      return 0;
    } else {
      return 1;
    }
}

