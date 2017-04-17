#include <iostream>
#include "bigInt.h"

using namespace std;

int main()
{
  BigInt n1(1280);
  n1 = (uint64_t)7;

  n1 = n1 & (uint128_t)5;
  n1.print();
 
  return 0;
}
