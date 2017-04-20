#include <iostream>
#include "BigInt.h"

using namespace std;

int main()
{
  BigInt x((uint64_t)0);
  BigInt y((uint128_t)1);

  if (x==y)
    cout << "== esta errado" << endl;
  else
    cout << "x == y" << endl;

  BigInt z((uint64_t)0);
  z = x + y;
  cout << "z=" << z << endl;

  z--;
  cout << "z--=" << z << endl;

  z = ~z;
  cout << "~z =" << z << endl;

  z = z & x;
  cout << "z&0=" << z << endl;

  z++;
  cout << "z++=" << z << endl;

  z = z << 4;
  cout << "z<<=" << z << endl;

  z = z >> 1;
  cout << "z>>=" << z << endl;

  return 0;
}
