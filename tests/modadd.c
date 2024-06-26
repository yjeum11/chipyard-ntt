#include "big_int.h"
#include <stdio.h>

int main(void) {
  BigInt a = 3856183;
  BigInt b = 12234224;
  BigInt modulus = 1837482;
  BigInt result;

  result = ModAddBigInt(a, b, modulus);

  if (result != 1390551) {
    return 0;
  } else {
    return 1;
  }
}
