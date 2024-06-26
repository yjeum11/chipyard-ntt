#include "rocc.h"

int main(void) {
  int modulus = 1231;
  int a = 413241;

  int k = 11;
  int mu = (1 << (2*k)) / modulus;

  int result = 856;
  
  // Load modulus
  ROCC_INSTRUCTION_S(0, modulus, 2);

  // Load mu
  ROCC_INSTRUCTION_S(0, mu, 3);

  // Compute quotient
  int q;
  ROCC_INSTRUCTION_DS(0, q, a, 0);

  // Compute result
  int r;
  ROCC_INSTRUCTION_DS(0, r, q, 1);

  if (r == result) {
    return 0;
  } else {
    return 1;
  }
}
