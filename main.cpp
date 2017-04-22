#include <iostream>
#include "bigInt.h"

using namespace std;

int main(int argc, char** argv)
{
  BigInt x(0);
  x = BigInt::pow2(atol(argv[1]));
  int l = BigInt::log2(x);

  cout << "2^" << atol(argv[1]) << "= " << x << endl;
  cout << "lg2x   = " << l << endl;

  return 0;
}
