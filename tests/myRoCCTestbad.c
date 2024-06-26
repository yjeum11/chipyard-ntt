#include "rocc.h"

int main(void) {
  int result = 0;

  // rd <- 2 * 5
  ROCC_INSTRUCTION_DSS(0, result, 2, 5, 1);

  if (result == 10) {
    return 1;
  } else {
    return 0;
  }
}
