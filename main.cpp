#include <iostream>
#include "bigInt.h"

using namespace std;

int main(int argc, char** argv)
{
  BigInt x(atol(argv[1]));

  cout << (x & 1) << endl;

  return 0;
}
