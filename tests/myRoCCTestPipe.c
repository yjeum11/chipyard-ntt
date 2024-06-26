#include "rocc.h"

int main(void) {
  int result = 0;
  int result2 = 0;
  int result3 = 0;
  int result4 = 0;

  // rd <- 2 * 5
  ROCC_INSTRUCTION_DSS(0, result, 2, 5, 1);
  ROCC_INSTRUCTION_DSS(0, result2, 2, 5, 1);
  ROCC_INSTRUCTION_DSS(0, result3, 2, 5, 1);
  ROCC_INSTRUCTION_DSS(0, result4, 2, 5, 1);

  if ( result == 10 && 
      result2 == 10 && 
      result3 == 10 && 
      result4 == 10) {
    return 0;
  } else {
    return 1;
  }
}
