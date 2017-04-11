#include <iostream>
#include "bigInt.h"

using namespace std;

int main()
{
  BigInt n1(1280);
  BigInt n2(640);
  n1 = 4;
  n1.print();
  n2.print();
  n2 = n1;
  n2.print();
  return 0;
}
