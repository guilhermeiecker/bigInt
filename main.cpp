#include <iostream>
#include "bigInt.h"

using namespace std;

int main()
{
  BigInt n1(256);
  BigInt n2(128);

  n1 = (uint128_t) 500;
  n2 = (uint128_t) 2;

  n1 = ~n1;
  n2 = ~n2;

  cout << (n2 < n1);

  return 0;
}
